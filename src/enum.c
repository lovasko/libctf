#include "enum.h"
#include "errors.h"

#include <stdint.h>
#include <stdlib.h>

int
ctf_enum_entry_get_name (struct ctf_enum_entry *enum_entry, char **out_name)
{
	if (enum_entry)
	{
		*out_name = enum_entry->name;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_enum_entry_get_value (struct ctf_enum_entry *enum_entry, int32_t **out_value)
{
	if (enum_entry)
	{
		*out_value = enum_entry->value;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_enum_get_name (struct ctf_enum *_enum, char **out_name)
{
	if (_enum && out_name)
	{
		*out_name = _enum->name;	
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_enum_get_next_entry (struct ctf_enum *_enum, 
    struct ctf_enum_entry *enum_entry, struct ctf_enum_entry **out_enum_entry)
{
	if (_enum)
	{
		if (enum_entry)
		{
			struct ctf_enum_entry *next = TAILQ_NEXT(enum_entry, entries);
			if (next == NULL)
				return CTF_END;
			else
			{
				*out_enum_entry = next;
				return CTF_OK;	
			}
		}
		else
		{
			if (TAILQ_EMPTY(_enum->enum_head))
				return CTF_EMPTY;

			*out_enum_entry = TAILQ_FIRST(_enum->enum_head);
		}

		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

