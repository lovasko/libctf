#include "read.h"
#include "header.h"
#include "util/compression.h"
#include "strings.h"
#include "file.h"
#include "data_object.h"
#include "kind.h"
#include "vardata.h"
#include "errors.h"
#include "array.h"

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

static struct _section*
elf_section_find (Elf *elf, Elf32_Ehdr *elf_header, const char *to_find)
{
	Elf_Scn *section = NULL;  	
	GElf_Shdr section_header;
	
	while ((section = elf_nextscn(elf, section)) != 0)
	{
		gelf_getshdr(section, &section_header);
		char *section_name = elf_strptr(elf, elf_header->e_shstrndx, 
		    section_header.sh_name);

		if (strcmp(section_name, to_find) == 0)
		{
			Elf_Data *data = elf_getdata(section, NULL);

			struct _section *result = malloc(_SECTION_SIZE);
			result->size = data->d_size;
			result->data = malloc(data->d_size);
			memcpy(result->data, data->d_buf, data->d_size);

			return result;
		}
	}

	return NULL;
}

static int
header_preface_check (struct _ctf_preface *preface)
{
	if (preface->magic != CTF_MAGIC)
		return CTF_E_MAGIC;

	if (preface->version != CTF_VERSION)
		return CTF_E_VERSION;

	return CTF_OK;
}

static int
read_functions_and_objects (struct ctf_file *file, struct _section
    *symtab_section, struct _section *object_section, struct _section
    *function_section, struct _strings *strings)
{
	size_t symbol_size = sizeof(Elf32_Sym);	
	unsigned int symbol_count = symtab_section->size / symbol_size;

	unsigned int object_offset = 0;
	unsigned int function_offset = 0;

	file->data_object_head = malloc(CTF_DATA_OBJECT_HEAD_SIZE);
	TAILQ_INIT(file->data_object_head);

	file->function_head = malloc(CTF_FUNCTION_HEAD_SIZE);
	TAILQ_INIT(file->function_head);

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
		uint16_t info;
		uint8_t vardata_length;
		struct ctf_function *function;
		struct ctf_argument *argument;
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

				TAILQ_INSERT_TAIL(file->data_object_head, data_object, data_objects);
			break;

			case STT_FUNC:
				info = *((uint16_t*)(function_section->data + function_offset));
				function_offset += sizeof(uint16_t);

				if (ctf_kind_from_info(info) == CTF_KIND_NONE && vardata_length == 0)
					break;
					
				vardata_length = info & CTF_VARDATA_LENGTH_MAX;

				function = malloc(CTF_FUNCTION_SIZE);
				function->name = strdup(name);
				function->argument_head = malloc(CTF_ARGUMENT_HEAD_SIZE);
				TAILQ_INIT(function->argument_head);
				for (unsigned int i = 0; i < vardata_length; i++)
				{
					type_reference = *((uint16_t*)(function_section->data 
					    + function_offset));
					function_offset += sizeof(uint16_t);

					argument = malloc(CTF_ARGUMENT_SIZE);				
					argument->type = lookup_type(file, type_reference);
					TAILQ_INSERT_TAIL(function->argument_head, argument, arguments);
				}

				type_reference = *((uint16_t*)(function_section->data + function_offset));
				function_offset += sizeof(uint16_t);
				function->return_type = lookup_type(file, type_reference);

				TAILQ_INSERT_HEAD(file->function_head, function, functions);
			break;
		}
	}

	return 0;
}

static int
read_labels (struct ctf_file *file, struct _section *section, struct
    _strings *strings)
{
	if (section->size % _CTF_LABEL_SIZE != 0)
		return CTF_E_LABEL_SECTION_CORRUPT;

	file->label_head = malloc(CTF_LABEL_HEAD_SIZE);
	TAILQ_INIT(file->label_head);

	struct _ctf_label *raw_labels = (struct _ctf_label*)section->data;	

	for (unsigned int i = 0; i < section->size/_CTF_LABEL_SIZE; i++)
	{
		struct ctf_label *to_add = malloc(CTF_LABEL_SIZE);
		to_add->index = raw_labels[i].index;
		to_add->name = strdup(strings_lookup(strings, raw_labels[i].name));
		TAILQ_INSERT_TAIL(file->label_head, to_add, labels);
	}

	return CTF_OK;
}

static int
solve_type_references (struct ctf_file *file)
{
	struct ctf_type *type;
	TAILQ_FOREACH (type, file->type_head, types)
	{
		if (ctf_kind_is_pure_reference(type->kind) == 1)
		{
			type->data = lookup_type(file, type->type_reference);
		}

		if (type->kind == CTF_KIND_ARRAY)
		{
			struct ctf_array *array = type->data;
			array->type = lookup_type(file, array->type_reference);
		}

		if (type->kind == CTF_KIND_STRUCT || type->kind == CTF_KIND_UNION)
		{
			struct ctf_member_head *member_head = type->data;
			struct ctf_member *member;
			TAILQ_FOREACH (member, member_head, members)
			{
				member->type = lookup_type(file, member->type_reference);
			}
		}

		if (type->kind == CTF_KIND_FUNC)
		{
			struct ctf_function *func = type->data;
			func->return_type = lookup_type(file, func->return_type_reference);

			struct ctf_argument *argument;
			TAILQ_FOREACH (argument, func->argument_head, arguments)
			{
				argument->type = lookup_type(file, argument->type_reference);
			}
		}
	}

	return 0;
}

static int
create_type_table (struct ctf_file *file)
{
	file->type_id_table = malloc(CTF_TYPE_SIZE * (file->type_count + 1));

	struct ctf_type *type;
	TAILQ_FOREACH (type, file->type_head, types)
	{
		file->type_id_table[type->id] = type;	
	}

	return 0;
}

static int
read_types (struct ctf_file *file, struct _section *section, struct
    _strings *strings)
{
	uint64_t offset = 0;	
	uint16_t id = 1;

	file->type_head = malloc(CTF_TYPE_HEAD_SIZE);
	TAILQ_INIT(file->type_head);

	file->type_count = 0;
	while (offset < section->size)
	{
		file->type_count++;

		struct _ctf_small_type *small_type = section->data + offset;	
		uint8_t kind = ctf_kind_from_info(small_type->info);
		uint16_t vardata_length = small_type->info & CTF_VARDATA_LENGTH_MAX;

		struct ctf_type *type = malloc(CTF_TYPE_SIZE);			
		type->kind = kind;
		type->id = id;

		id++;

		if (ctf_kind_is_pure_reference(kind) == 1)
		{
			if (kind == CTF_KIND_TYPEDEF)
				type->name = strdup(strings_lookup(strings, small_type->name));
			else
				type->name = NULL;

			type->type_reference = small_type->type;

			offset += _CTF_SMALL_TYPE_SIZE;
		}

		if (kind == CTF_KIND_NONE)
		{
			type->name = NULL;
			type->data = NULL;

			offset += _CTF_SMALL_TYPE_SIZE;
		}

		if (kind == CTF_KIND_FWD_DECL)
		{
			type->name = strdup(strings_lookup(strings, small_type->name));		
			type->type_reference = small_type->type;

			offset += _CTF_SMALL_TYPE_SIZE;
		}

		if (ctf_kind_is_complex(kind) == 1 && kind != CTF_KIND_FUNC)
		{
			uint64_t advance = _CTF_SMALL_TYPE_SIZE;
			uint16_t size = small_type->size;
			if (small_type->size > CTF_SMALL_TYPE_THRESHOLD)
			{
				struct _ctf_large_type *large_type = section->data + offset;
				size = large_type->size;
				advance	+= (_CTF_LARGE_TYPE_SIZE - _CTF_SMALL_TYPE_SIZE);
			}
			offset += advance;

			type->name = strdup(strings_lookup(strings, small_type->name));

			switch (kind)
			{
				case CTF_KIND_INT:
				case CTF_KIND_FLOAT:
					type->data = read_int_float_vardata(section->data + offset);
					offset += 4;
				break;

				case CTF_KIND_ARRAY:
					type->data = read_array_vardata(section->data + offset);
					offset += _CTF_ARRAY_SIZE;
				break;

				case CTF_KIND_ENUM:
					type->data = read_enum_vardata(section->data + offset, vardata_length, 
					    strings);
					offset += vardata_length * _CTF_ENUM_ENTRY_SIZE;
				break;

				case CTF_KIND_STRUCT:
				case CTF_KIND_UNION:
					type->data = read_struct_union_vardata(section->data + offset,
					    vardata_length, size, strings);
					offset += vardata_length * (small_type->size >= CTF_MEMBER_THRESHOLD ? 
					    _CTF_LARGE_MEMBER_SIZE : _CTF_SMALL_MEMBER_SIZE);
				break;
			}
		}

		/* 
		 * We need to handle the function type with special touch, since it is a
		 * combination of both reference and complex type: it uses rather type then
		 * size from the small_type union but still needs additional parsing of the
		 * vardata. But we can not afford to check the type against the
		 * SMALL_TYPE_THRESHOLD and potentially load the large_type, which would
		 * make us skip either 4 arguments or even cut the header of next type.
		 */
		if (kind == CTF_KIND_FUNC)
		{
			offset += _CTF_SMALL_TYPE_SIZE;

			type->name = strdup(strings_lookup(strings, small_type->name));
			type->data = read_function_vardata(section->data + offset, vardata_length);

			((struct ctf_function*)type->data)->return_type_reference = 
			    small_type->type;

			offset += (vardata_length + (vardata_length & 1)) * sizeof(uint16_t);
		}

		TAILQ_INSERT_TAIL(file->type_head, type, types);
	}

	create_type_table(file);
	solve_type_references(file);

	return 0;
}

int
ctf_read_file (char *filename, struct ctf_file **out_file)
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
		return CTF_E_NO_CTF_SECTION;

	/* find the string table section */
	struct _section *strtab_section = elf_section_find(elf, &elf_header,
	    CTF_ELF_SECTION_STRTAB);
	if (strtab_section == NULL)
		return CTF_E_NO_STRTAB;

	/* find the symbol table section */
	struct _section *symtab_section = elf_section_find(elf, &elf_header,
	    CTF_ELF_SECTION_SYMTAB);
	if (symtab_section == NULL)
		return CTF_E_NO_SYMTAB;

	/* we do not need the ELF data anymore */
	elf_end(elf);

	/* read the CTF header */
	struct _ctf_header *header = (struct _ctf_header*)ctf_section->data;
	int header_status;
	if ((header_status = header_preface_check(&header->preface)) != 0)
		return header_status;

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
			return CTF_E_COMPRESSION;

		if (decompressed->size != header->string_offset + header->string_length)
			return CTF_E_DECOMPRESSED_DATA_SIZE;

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
		if ((ctf_read_file(parent_basename, &file->parent_file)) != CTF_OK)
			return retval;

		char *parent_label_name = strings_lookup(&strings, header->parent_label);
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
	if ((retval = read_labels(file, &label_section, &strings)) != CTF_OK)
		return retval;

	/* read the types */
	struct _section type_section;
	type_section.data = headerless_ctf + header->type_offset;
	type_section.size = header->string_offset - header->type_offset;
	if ((retval = read_types(file, &type_section, &strings)) != CTF_OK)
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
	if ((retval = read_functions_and_objects(file, symtab_section, &object_section,
	    &function_section, &strings)) != CTF_OK)
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

