#include "io/read/objects.h"
#include "io/read/lookup.h"
#include "space.h"
#include "type/info.h"

#ifdef _KERNEL
	#include <sys/elf.h>
	#include <sys/malloc.h>
#else
	#include <libelf.h>
	#include <stdlib.h>
	#include <string.h>
#endif

CTF_MALLOC_DECLARE(M_CTF);

int
_ctf_read_functions_and_objects (
    struct ctf_file* file, 
		struct _section* symtab_section, 
		struct _section* object_section, 
		struct _section* function_section, 
		struct _strings* strings)
{
	size_t symbol_size = sizeof(Elf32_Sym);	
	unsigned int symbol_count = symtab_section->size / symbol_size;

	unsigned int object_offset = 0;
	unsigned int function_offset = 0;

	file->data_object_head = CTF_MALLOC(CTF_DATA_OBJECT_HEAD_SIZE);
	TAILQ_INIT(file->data_object_head);

	file->function_head = CTF_MALLOC(CTF_FUNCTION_HEAD_SIZE);
	TAILQ_INIT(file->function_head);

	for (unsigned int i = 0; i < symbol_count; i++)
	{
		Elf32_Sym* symbol = (Elf32_Sym*)(symtab_section->data + i * symbol_size);

		/* FIXME strings->elf can be NULL */
		char* name;
		if (symbol->st_name < strings->elf->size)
			name = strings->elf->data + symbol->st_name;
		else
			name = NULL;

		if (symbol->st_name == 0)
			continue;

		if (symbol->st_shndx == SHN_UNDEF)
			continue;

		if (strcmp(name, "_START_") == 0)
			continue;
			
		if (strcmp(name, "_END_") == 0)
			continue;

		uint16_t type_reference;
		uint16_t info;
		uint8_t vardata_length;
		struct ctf_function* function;
		struct ctf_argument* argument;

		uint16_t* fp = (uint16_t*)(function_section->data);

		switch (ELF32_ST_TYPE(symbol->st_info))
		{
			case STT_OBJECT:
				if (symbol->st_shndx == SHN_ABS && symbol->st_value == 0)
					break;

				type_reference = *((uint16_t*)(object_section->data + object_offset));
				object_offset += sizeof(uint16_t);

				struct ctf_data_object* data_object = CTF_MALLOC(CTF_DATA_OBJECT_SIZE);
				data_object->name = CTF_STRDUP(name);
				data_object->type = _ctf_lookup_type(file, type_reference);

				TAILQ_INSERT_TAIL(file->data_object_head, data_object, data_objects);
			break;

			case STT_FUNC:
				info = *(fp + function_offset);
				function_offset++;

				vardata_length = _ctf_info_get_vardata_length(info);
				if (_ctf_info_get_kind(info) == CTF_KIND_NONE 
				 && vardata_length == 0)
					break;

				type_reference = *(fp + function_offset);
				function_offset++;

				function = CTF_MALLOC(CTF_FUNCTION_SIZE);
				function->name = CTF_STRDUP(name);
				function->argument_head = CTF_MALLOC(CTF_ARGUMENT_HEAD_SIZE);
				function->return_type = _ctf_lookup_type(file, type_reference);

				TAILQ_INIT(function->argument_head);
				for (unsigned int k = 0; k < vardata_length; k++)
				{
					type_reference = *(fp + function_offset);
					function_offset++;

					argument = CTF_MALLOC(CTF_ARGUMENT_SIZE);				
					argument->type = _ctf_lookup_type(file, type_reference);
					TAILQ_INSERT_TAIL(function->argument_head, argument, arguments);
				}
				
				TAILQ_INSERT_TAIL(file->function_head, function, functions);
			break;
		}
	}

	return CTF_OK;
}

