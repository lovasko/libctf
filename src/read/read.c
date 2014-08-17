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
#elif
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
	int rv;

	/* check for presence of the essential data */
	if (ctf_data->data == NULL || ctf_data->size == 0)
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
	strings.elf = strtab_section;

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
ctf_file_read (const char* filename, ctf_file* out_file)
{
	int retval; 

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
	Elf *elf = NULL;
	if ((elf = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
	{
		close(fd);
		return CTF_E_ELF_OPEN;
	}

	/* find the CTF section */
	struct _section *ctf_section = elf_section_find(elf, &elf_header,
	    CTF_ELF_SECTION_SUNW_CTF);
	if (ctf_section == NULL)
	{
		elf_end(elf);
		return CTF_E_NO_CTF_SECTION;
	}

	/* find the string table section */
	struct _section *strtab_section = elf_section_find(elf, &elf_header,
	    CTF_ELF_SECTION_STRTAB);
	if (strtab_section == NULL)
	{
		free(ctf_section->data);
		free(ctf_section);
		elf_end(elf);
		return CTF_E_NO_STRTAB;
	}

	/* find the symbol table section */
	struct _section *symtab_section = elf_section_find(elf, &elf_header,
	    CTF_ELF_SECTION_SYMTAB);
	if (symtab_section == NULL)
		return CTF_E_NO_SYMTAB;

	/* we do not need the ELF data anymore */
	elf_end(elf);

	/* construct the final file structure */
	struct ctf_file *file = malloc(CTF_FILE_SIZE);
	file->version = _CTF_VERSION_2;
	file->is_compressed = header->preface.flags & _CTF_FLAG_COMPRESSED;

	char* filename_copy = strdup(filename);
	file->path_basename = strdup(basename(filename_copy));
	free(filename_copy);

	/* check for the parent reference */
	const char *parent_basename = _ctf_strings_lookup(&strings, 
	    header->parent_basename);
	if (parent_basename[0] !=	'\0')
	{
		/* TODO is this really a basename? if so, we need to extract the dirname to
		 * be able to locate the file properly. For the future - why isnt this a
		 * full path? */
		if ((ctf_file_read(parent_basename, &file->parent_file)) != CTF_OK)
			return retval;

		const char *parent_label_name = _ctf_strings_lookup(&strings, 
		    header->parent_label);
		struct ctf_label *parent_label;
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

	/* read the labels */
	struct _section label_section;
	label_section.data = headerless_ctf + header->label_offset;
	label_section.size = header->object_offset - header->label_offset;
	if ((retval = _ctf_read_labels(file, &label_section, &strings)) != CTF_OK)
		return retval;

	/* read the types */
	struct _section type_section;
	type_section.data = headerless_ctf + header->type_offset;
	type_section.size = header->string_offset - header->type_offset;
	if ((retval = _ctf_read_types(file, &type_section, &strings)) != CTF_OK)
		return retval;

	/* TODO here should be check for some kind of flag that will be argument of
	 * this function "read types only" so we do not bother loading the function
	 * and object data. */

	struct _section object_section;
	object_section.data = headerless_ctf + header->object_offset;
	object_section.size = header->function_offset - header->object_offset;
	struct _section function_section;
	function_section.data = headerless_ctf + header->function_offset;
	function_section.size = header->type_offset - header->function_offset;
	if ((retval = _ctf_read_functions_and_objects(file, symtab_section, 
	    &object_section, &function_section, &strings)) != CTF_OK)
		return retval;

	free(ctf_section->data);
	free(ctf_section);
	free(strtab_section->data);
	free(strtab_section);
	free(symtab_section->data);
	free(symtab_section);
	free(strings.ctf);
	close(fd);

	*out_file = file;
	return CTF_OK;
}

#endif /* not _KERNEL */

