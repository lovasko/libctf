#include "enum_entry.h"
#include "errors.h"

#include <stdint.h>
#include <stdlib.h>

int
ctf_enum_entry_get_name (struct ctf_enum_entry *enum_entry, char **out_name)
{
	if (enum_entry && out_name)
	{
		*out_name = enum_entry->name;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_enum_entry_get_value (struct ctf_enum_entry *enum_entry, 
    int32_t **out_value)
{
	if (enum_entry && out_value)
	{
		*out_value = enum_entry->value;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

