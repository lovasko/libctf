#include "read.h"
#include "vardata.h"
#include "header.h"
#include "strings.h"
#include "decompress.h"
#include "lookup.h"
#include "labels.h"
#include "types.h"
#include "objects.h"
#include "space.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/queue.h>

#ifdef _KERNEL
	#include <sys/param.h>
	#include <sys/kernel.h>
	#include <sys/malloc.h>
	#include <sys/libkern.h>
	#include <sys/elf.h>
#else
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <fcntl.h>
	#include <libelf.h>
	#include <gelf.h>
	#include <stdint.h>
	#include <libgen.h>
#endif

int
ctf_file_read_data (
    struct _section* ctf_data, 
    struct _section* symbol_table, 
    struct _section* string_table,
    ctf_file* file)
{
	/* return value */
	int rv;

	/* check for presence of the essential data */
	if (ctf_data == NULL || ctf_data->data == NULL || ctf_data->size == 0)
		return CTF_E_NO_CTF_SECTION;

	/* read the CTF header */
	struct _ctf_header* header = (struct _ctf_header*)ctf_section->data;
	if ((rv = _ctf_preface_check(&header->preface)) != CTF_OK)
		return rv;

	/* check the order of offsets */
	if ((rv = _ctf_header_offset_sanity_check(header)) != CTF_OK)
		return rv;

	/* pointer to decompressed start of the actual CTF data without the header */
	void* headerless_ctf;

#ifdef _KERNEL
	/* 
	 * we do not provide decompression inside kernel space, as this functionality
	 * is already contained in the linker_ctf_get 
	 */
	headerless_ctf = ctf_data->data + _CTF_HEADER_SIZE;
#elif
	/* decompress the CTF data (if compressed) */
	if (header->preface.flags & _CTF_FLAG_COMPRESSED)
	{
		struct _section compressed;
		compressed.data = ctf_data->data + _CTF_HEADER_SIZE;
		compressed.size = ctf_data->size - _CTF_HEADER_SIZE;

		struct _section* decompressed = _ctf_decompress(&compressed);	
		if (decompressed == NULL)
			return CTF_E_COMPRESSION;

		/* FIXME dealloc */
		if (decompressed->size != header->string_offset + header->string_length)
			return CTF_E_DECOMPRESSED_DATA_SIZE;

		headerless_ctf = decompressed->data;
		free(decompressed);
	}
	else
		headerless_ctf = ctf_data->data + _CTF_HEADER_SIZE;
#endif

	/* construct the string table data structure */
	struct _strings strings;
	strings.ctf = CTF_MALLOC(_SECTION_SIZE);
	strings.ctf->data = headerless_ctf + header->string_offset;
	strings.ctf->size = header->string_length;

	/* check the presence of the ELF string table and handle the absence of it */
	if (string_table == NULL || string_table->data == NULL 
	 || string_table->size == 0)
		strings.elf = NULL;
	else
		strings.elf = strtab_section;

	/* construct the final file structure */
	struct ctf_file* file = CTF_MALLOC(CTF_FILE_SIZE);
	file->version = _CTF_VERSION_2;
	file->is_compressed = header->preface.flags & _CTF_FLAG_COMPRESSED;

	char* filename_copy = CTF_STRDUP(filename);

#ifdef _KERNEL
	/* TODO basename in kernel space */
	file->path_basename = CTF_STRDUP(filename_copy);
#elif
	file->path_basename = CTF_STRDUP(basename(filename_copy));
#endif

	CTF_FREE(filename_copy);

#ifdef _KERNEL
	/* primary use inside kernel is the DDB - and there is no notion of file
	 * names or file systems, therefore no parent file name is recognized */
	file->parent_file = NULL;
	file->type_id_offset = 0;
#elif
	/* check for the parent reference */
	const char* parent_basename = _ctf_strings_lookup(&strings, 
	    header->parent_basename);
	if (parent_basename[0] !=	'\0')
	{
		/* TODO is this really a basename? if so, we need to extract the dirname to
		 * be able to locate the file properly. For the future - why isnt this a
		 * full path? */
		if ((ctf_file_read(parent_basename, &file->parent_file)) != CTF_OK)
			return retval;

		const char* parent_label_name = _ctf_strings_lookup(&strings, 
		    header->parent_label);
		struct ctf_label* parent_label;

		int found = 0;
		TAILQ_FOREACH (parent_label, file->parent_file->label_head, labels)
		{
			if (strcmp(parent_label_name, parent_label->name) == 0)
			{
				found = 1;	
				break;
			}
		}

		if (found == 0)
			return CTF_E_PARENT_LABEL_NOT_FOUND;
		else
			file->type_id_offset = parent_label->index;
	}
	else
	{
		file->parent_file = NULL;
		file->type_id_offset = 0;
	}
#endif

	/* read the labels */
	struct _section label_section;
	label_section.data = headerless_ctf + header->label_offset;
	label_section.size = header->object_offset - header->label_offset;
	if ((rv = _ctf_read_labels(file, &label_section, &strings)) != CTF_OK)
		return rv;

	/* read the types */
	struct _section type_section;
	type_section.data = headerless_ctf + header->type_offset;
	type_section.size = header->string_offset - header->type_offset;
	if ((rv = _ctf_read_types(file, &type_section, &strings)) != CTF_OK)
		return rv;

	/* TODO here should be check for some kind of flag that will be argument of
	 * this function "read types only" so we do not bother loading the function
	 * and object data. */

	if (symbol_table == NULL || symbol_table->data == NULL 
	 || symbol_table->size == 0)
	{
		/* in case that the symbol table is not available, we init the function and
		 * data object lists to be empty */
		file->data_object_head = CTF_MALLOC(CTF_DATA_OBJECT_HEAD_SIZE);
		TAILQ_INIT(file->data_object_head);

		file->function_head = CTF_MALLOC(CTF_FUNCTION_HEAD_SIZE);
		TAILQ_INIT(file->function_head);
	}
	else
	{
		struct _section object_section;
		object_section.data = headerless_ctf + header->object_offset;
		object_section.size = header->function_offset - header->object_offset;
		struct _section function_section;
		function_section.data = headerless_ctf + header->function_offset;
		function_section.size = header->type_offset - header->function_offset;
		if ((rv = _ctf_read_functions_and_objects(file, symtab_section, 
				&object_section, &function_section, &strings)) != CTF_OK)
			return rv;
	}

	return CTF_OK;
}

#ifndef _KERNEL

#define CTF_ELF_SECTION_SYMTAB ".symtab"
#define CTF_ELF_SECTION_STRTAB ".strtab"
#define CTF_ELF_SECTION_SUNW_CTF ".SUNW_ctf"

/**
 * Find an ELF section with specified name.
 *
 * @param [in] elf ELF file
 * @param [in] elf_header ELF file header
 * @param [in] to_find section name to find
 * @return section data on success, NULL otherwise
 */
static struct _section*
elf_section_find (Elf* elf, Elf32_Ehdr* elf_header, const char* to_find)
{
	Elf_Scn* section = NULL;  	
	GElf_Shdr section_header;
	
	while ((section = elf_nextscn(elf, section)) != 0)
	{
		gelf_getshdr(section, &section_header);
		char* section_name = elf_strptr(elf, elf_header->e_shstrndx, 
		    section_header.sh_name);

		if (strcmp(section_name, to_find) == 0)
		{
			Elf_Data* data = elf_getdata(section, NULL);

			struct _section* result = malloc(_SECTION_SIZE);
			result->size = data->d_size;
			result->data = malloc(data->d_size);
			memcpy(result->data, data->d_buf, data->d_size);

			return result;
		}
	}

	return NULL;
}

int
ctf_file_read (const char* filename, ctf_file* file)
{
	int rv; 

	/* open the file */
	int fd;
	if ((fd = open(filename, O_RDONLY)) < 0)
		return CTF_E_NO_FILE;

	/* read the ELF header */
	Elf32_Ehdr elf_header;
	if (read(fd, &elf_header, sizeof(Elf32_Ehdr)) != sizeof(Elf32_Ehdr))
	{
		close(fd);
		return CTF_E_ELF_HEADER_CORRUPT;
	}

	/* set the libelf version */
	if (elf_version(EV_CURRENT) == EV_NONE)
	{
		close(fd);
		return CTF_E_ELF_VERSION;
	}

	/* load the ELF file */
	Elf* elf = NULL;
	if ((elf = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
	{
		close(fd);
		return CTF_E_ELF_OPEN;
	}

	/* find the CTF section */
	struct _section* ctf_section = elf_section_find(elf, &elf_header,
	    CTF_ELF_SECTION_SUNW_CTF);

	/* find the string table section */
	struct _section* strtab_section = elf_section_find(elf, &elf_header,
	    CTF_ELF_SECTION_STRTAB);

	/* find the symbol table section */
	struct _section* symtab_section = elf_section_find(elf, &elf_header,
	    CTF_ELF_SECTION_SYMTAB);

	/* we do not need the ELF data anymore */
	elf_end(elf);

	/* call the raw data parsing function */
	rv = ctf_file_read_data(ctf_section, strtab_section, symtab_section, file);

	free(ctf_section->data);
	free(ctf_section);
	free(strtab_section->data);
	free(strtab_section);
	free(symtab_section->data);
	free(symtab_section);
	close(fd);

	return rv;
}

#endif /* not _KERNEL */

