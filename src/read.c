#include "read.h"
#include "header.h"
#include "util/compression.h"
#include "util/elf_section_find.h"
#include "strings.h"
#include "file.h"
#include "data_object.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/queue.h>
#include <fcntl.h>
#include <libelf.h>
#include <gelf.h>
#include <stdint.h>

static int
header_preface_check (struct _ctf_preface *preface)
{
	if (preface->magic != CTF_MAGIC)
		return 1;

	if (preface->version != CTF_VERSION)
		return 2;

	return 0;
}

int
read_functions_and_objects (struct ctf_file *file, struct _section
    *symtab_section, struct _section *object_section, struct _section
    *function_section, struct _strings *strings)
{
	size_t symbol_size = sizeof(Elf32_Sym);	
	unsigned int symbol_count = symtab_section->size / symbol_size;

	unsigned int object_offset = 0;
	unsigned int function_offset = 0;

	file->data_object_head = malloc(CTF_DATA_OBJECT_HEAD_SIZE);
	LIST_INIT(file->data_object_head);

	for (unsigned int i = 0; i < symbol_count; i++)
	{
		Elf32_Sym *symbol = (Elf32_Sym*)(symtab_section->data + i * symbol_size);

		char *name;
		if (symbol->st_name < strings->elf->size)
			name = strings->elf->data + symbol->st_name;
		else
			name = NULL;

		if (symbol->st_name == 0 || symbol->st_shndx == SHN_UNDEF || 
		    strcmp(name, "_START_") == 0 || strcmp(name, "_END_") == 0)
			continue;

		uint16_t type_reference;
		switch (ELF32_ST_TYPE(symbol->st_info))
		{
			case STT_OBJECT:
				if (symbol->st_shndx == SHN_ABS && symbol->st_value == 0)
					break;

				type_reference = *((uint16_t*)(object_section->data + object_offset));
				object_offset += sizeof(uint16_t);

				struct ctf_data_object *data_object = malloc(CTF_DATA_OBJECT_SIZE);
				data_object->name = strdup(name);
				data_object->type = lookup_type(file, type_reference);

				LIST_INSERT_HEAD(file->data_object_head, data_object, data_objects);
			break;

			case STT_FUNC:
				printf("Function!\n");
			break;
		}
	}

	return 0;
}

struct ctf_file*
ctf_read_file (char *filename)
{
	/* open the file */
	int fd;
	if ((fd = open(filename, O_RDONLY)) < 0)
		return NULL;

	/* read the ELF header */
	Elf32_Ehdr elf_header;
	if (read(fd, &elf_header, sizeof(Elf32_Ehdr)) != sizeof(Elf32_Ehdr))
	{
		close(fd);
		return NULL;
	}

	/* set the libelf version */
	if (elf_version(EV_CURRENT) == EV_NONE)
	{
		close(fd);
		return NULL;
	}

	/* load the ELF file */
	Elf *elf = NULL;
	if ((elf = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
	{
		close(fd);
		return NULL;
	}

	/* find the CTF section */
	struct _section *ctf_section = elf_section_find(elf, &elf_header,
	    CTF_ELF_SECTION_SUNW_CTF);
	if (ctf_section == NULL)
		return NULL;

	/* find the string table section */
	struct _section *strtab_section = elf_section_find(elf, &elf_header,
	    CTF_ELF_SECTION_STRTAB);
	if (strtab_section == NULL)
		return NULL;

	/* find the symbol table section */
	struct _section *symtab_section = elf_section_find(elf, &elf_header,
	    CTF_ELF_SECTION_SYMTAB);
	if (symtab_section == NULL)
		return NULL;

	/* we do not need the ELF data anymore */
	elf_end(elf);

	/* read the CTF header */
	struct _ctf_header *header = (struct _ctf_header*)ctf_section->data;
	if (header_preface_check(&header->preface) != 0)
		return NULL;

	/* pointer to decompressed start of the actual CTF data without the header */
	void *headerless_ctf;

	/* decompress the CTF data (if compressed) */
	if (header->preface.flags & CTF_COMPRESSED)
	{
		struct _section compressed;
		compressed.data = ctf_section->data + _CTF_HEADER_SIZE;
		compressed.size = ctf_section->size - _CTF_HEADER_SIZE;

		struct _section *decompressed = decompress(&compressed);	
		if (decompressed == NULL)
			return NULL;

		if (decompressed->size != header->string_offset + header->string_length)
			return NULL;

		headerless_ctf = decompressed->data;
	}
	else
		headerless_ctf = ctf_section->data + _CTF_HEADER_SIZE;

	/* construct the string table data structure */
	struct _strings strings;
	strings.ctf = malloc(_SECTION_SIZE);
	strings.ctf->data = headerless_ctf + header->string_offset;
	strings.ctf->size = header->string_length;
	strings.elf = strtab_section;

	/* construct the final file structure */
	struct ctf_file *file = malloc(CTF_FILE_SIZE);
	file->version = CTF_VERSION;
	file->compressed = header->preface.flags & CTF_COMPRESSED;

	/* check for the parent reference */
	char *parent_basename = strings_lookup(&strings, header->parent_basename);
	if (parent_basename[0] !=	'\0')
	{
		/* TODO is this really a basename? if so, we need to extract the dirname to
		 * be able to locate the file properly. For the future - why isnt this a
		 * full path? */
		file->parent_file = ctf_read_file(parent_basename);
		if (file->parent_file == NULL)
			return NULL;

		char *parent_label_name = strings_lookup(&strings, header->parent_label);
		struct ctf_label *parent_label;
		int found = 0;

		LIST_FOREACH (parent_label, file->parent_file->label_head, labels)
		{
			if (strcmp(parent_label_name, parent_label->name) == 0)
			{
				found = 1;	
				break;
			}
		}

		if (found == 0)
			return NULL;
		else
		{
			file->type_id_offset = parent_label->index;
		}
	}
	else
	{
		file->parent_file = NULL;
		file->type_id_offset = 0;
	}

	/* read the labels */
	struct _section label_section;
	label_section.data = headerless_ctf + header->label_offset;
	label_section.size = header->object_offset - header->label_offset;
	read_labels(file, &label_section, &strings);

	/* read the types */
	struct _section type_section;
	type_section.data = headerless_ctf + header->type_offset;
	type_section.size = header->string_offset - header->type_offset;
	read_types(file, &type_section, &strings);

	/* TODO here should be check for some kind of flag that will be argument of
	 * this function "read types only" so we do not bother loading the function
	 * and object data. */

	struct _section object_section;
	object_section.data = headerless_ctf + header->object_offset;
	object_section.size = header->function_offset - header->object_offset;

	struct _section function_section;
	function_section.data = headerless_ctf + header->function_offset;
	function_section.size = header->type_offset - header->function_offset;

	read_functions_and_objects(file, symtab_section, &object_section,
	    &function_section, &strings);

	free(ctf_section->data);
	free(ctf_section);
	free(strtab_section->data);
	free(strtab_section);
	free(symtab_section->data);
	free(symtab_section);
	free(strings.ctf);
	close(fd);

	return file;
}

