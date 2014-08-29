#include "strings.h"

const char*
_ctf_strings_lookup (struct _strings* strings, uint32_t reference)
{
	unsigned int table_id = reference >> 31;	
	uint32_t offset = reference & 0x7fffffff;

	if (table_id == 0)
	{
		if (strings->ctf->size < offset)
			return NULL;
		else
			return &((const char*)strings->ctf->data)[offset];
	}

	if (table_id == 1)
	{
		if (strings->elf == NULL)
			return "N/A";

		if (strings->elf->size < offset)
			return NULL;
		else
			return &((const char*)strings->elf->data)[offset];
	}

	return NULL;
}

