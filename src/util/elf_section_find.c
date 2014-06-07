#include "util/elf_section_find.h"

#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <gelf.h>

struct _section*
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

