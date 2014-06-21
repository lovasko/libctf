#include "enum.h"

#include <stdint.h>
#include <stdlib.h>

char*
ctf_enum_entry_get_name (struct ctf_enum_entry *enum_entry)
{
	if (enum_entry)
		return enum_entry->name;
	else
		return NULL;
}

int32_t
ctf_enum_entry_get_value (struct ctf_enum_entry *enum_entry)
{
	if (enum_entry)
		return enum_entry->value;
	else
		return 0;
}

