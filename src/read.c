#include "read.h"
#include "header.h"
#include "type.h"
#include "kind.h"
#include "vardata.h"
#include "array.h"
#include "member.h"
#include "enum.h"

#include <stdlib.h>
#include <string.h>

char *ctf_string_table;
char *elf_string_table;

/* TODO check bounds for both tables */
static char*
resolve_string (uint32_t name_reference)
{
	uint32_t offset = name_reference & 0x7fffffff;

	if ((name_reference >> 31) == 0)
		return &ctf_string_table[offset];
	else
		return &elf_string_table[offset];
}

static int
header_preface_check (struct _ctf_preface *preface)
{
	if (preface->magic != CTF_MAGIC)
		return 1;

	if (preface->version != CTF_VERSION)
		return 2;

	return 0;
}

struct ctf_file*
ctf_read_file (char *filename)
{
	struct _ctf_header header;
	memcpy(&header, ctf.data, _CTF_HEADER_SIZE);

	if (header_preface_check(&header.preface) != 0)
		return NULL;

	ctf_string_table = ctf.data + _CTF_HEADER_SIZE + header.string_offset;
	elf_string_table = elf_strtab.data;

	struct ctf_section label_section;
	label_section.data = ctf.data + _CTF_HEADER_SIZE + header.label_offset;
	label_section.size = header.object_offset - header.label_offset;

	struct ctf_label_head label_head;	
	LIST_INIT(&label_head);
	read_labels(&label_head, &label_section);

	struct ctf_section type_section;
	type_section.data = ctf.data + _CTF_HEADER_SIZE + header.type_offset;
	type_section.size = header.string_offset - header.type_offset;

	struct ctf_type_head type_head;	
	LIST_INIT(&type_head);
	read_types(&type_head, &type_section);

	struct ctf_file *file = malloc(CTF_FILE_SIZE);
	file->label_head = label_head;
	file->type_head = type_head;
	file->version = CTF_VERSION;
	file->compressed = 0;

	return file;
}

