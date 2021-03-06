#ifdef _KERNEL
	#include <sys/elf.h>
	#include <sys/malloc.h>
#else
	#include <libelf.h>
	#include <gelf.h>
	#include <stdlib.h>
	#include <string.h>
#endif

#include "io/read/read.h"
#include "space.h"
#include "type/info.h"

CTF_MALLOC_DECLARE();

int
_ctf_read_functions_and_objects(struct ctf_file* file,
                                struct _section* symtab,
                                struct _section* object_section,
                                struct _section* function_section,
                                struct _strings* strings)
{
	unsigned int i;
	unsigned int k;
	unsigned int object_offset;
	unsigned int function_offset;
	char* name;
	GElf_Sym symbol;
	uint16_t type_reference;
	uint16_t info;
	uint8_t vardata_length;
	struct ctf_function* function;
	struct ctf_argument* argument;

	object_offset = 0;
	function_offset = 0;

	m_list_init(&file->data_objects);
	m_list_init(&file->function_objects);

	if (symtab == NULL || strings == NULL || strings->elf == NULL)
		return CTF_OK;

	for (i = 0; ; i++)
	{
		if (gelf_getsym(symtab->elf_data, i, &symbol) == NULL)
			break;

		if (symbol.st_name < strings->elf->size)
			name = strings->elf->data + symbol.st_name;
		else
			continue;

		if (symbol.st_name == 0)
			continue;

		if (symbol.st_shndx == SHN_UNDEF)
			continue;

		if (strcmp(name, "_START_") == 0)
			continue;
			
		if (strcmp(name, "_END_") == 0)
			continue;


		uint16_t* fp = (uint16_t*)(function_section->data);

		switch (GELF_ST_TYPE(symbol.st_info))
		{
			case STT_OBJECT:
				if (symbol.st_shndx == SHN_ABS && symbol.st_value == 0)
					break;

				type_reference = *((uint16_t*)(object_section->data + object_offset));
				object_offset += sizeof(uint16_t);

				struct ctf_data_object* data_object = CTF_MALLOC(CTF_DATA_OBJECT_SIZE);
				data_object->name = CTF_STRDUP(name);
				data_object->type = _ctf_lookup_type(file, type_reference);
				data_object->value = symbol.st_value;
				data_object->size = symbol.st_size;

				m_list_append(&file->data_objects, M_LIST_COPY_SHALLOW, data_object, 0);
			break;

			case STT_FUNC:
				info = *(fp + function_offset);
				function_offset++;

				vardata_length = _ctf_info_get_vardata_length(info);
				if (_ctf_info_get_kind(info) == CTF_KIND_NONE && vardata_length == 0)
					break;

				type_reference = *(fp + function_offset);
				function_offset++;

				function = CTF_MALLOC(CTF_FUNCTION_SIZE);
				function->name = CTF_STRDUP(name);
				function->return_type = _ctf_lookup_type(file, type_reference);
				m_list_init(&function->arguments);

				for (k = 0; k < vardata_length; k++)
				{
					type_reference = *(fp + function_offset);
					function_offset++;

					argument = CTF_MALLOC(CTF_ARGUMENT_SIZE);				
					argument->type = _ctf_lookup_type(file, type_reference);
					m_list_append(&function->arguments, M_LIST_COPY_SHALLOW, argument, 0);
				}
				
				m_list_append(&file->function_objects, M_LIST_COPY_SHALLOW, function, 0);
			break;
		}
	}

	return CTF_OK;
}

