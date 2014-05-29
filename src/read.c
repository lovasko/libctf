#include "read.h"
#include "header.h"
#include "type.h"
#include "kind.h"

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
read_labels (struct ctf_label_head *head, struct ctf_section *section)
{
	if (section->size % _CTF_LABEL_SIZE != 0)
		return 1;

	struct _ctf_label *raw_labels = (struct _ctf_label*)section->data;	

	for (unsigned int i = 0; i < section->size/_CTF_LABEL_SIZE; i++)
	{
		struct ctf_label *to_add = (struct ctf_label*)malloc(CTF_LABEL_SIZE);
		to_add->index = raw_labels[i].index;
		to_add->name = resolve_string(raw_labels[i].name);
		ctf_label_add(head, to_add);
	}

	return 0;
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
ctf_read_buffer (struct ctf_section ctf, struct ctf_section elf_strtab)
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

	struct ctf_file *file = (struct ctf_file*)malloc(CTF_FILE_SIZE);
	file->label_head = label_head;
	file->version = CTF_VERSION;
	file->compressed = 0;

	return file;
}

