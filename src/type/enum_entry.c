#include <string.h>

#include "type/enum_entry.h"

_CTF_GET_PROPERTY_IMPL(
	ctf_enum_entry_get_name,
	ctf_enum_entry,
	char*,
	name)

_CTF_SET_PROPERTY_IMPL(
	ctf_enum_entry_set_name,
	ctf_enum_entry,
	char*,
	name)

_CTF_GET_PROPERTY_IMPL(
	ctf_enum_entry_get_value,
	ctf_enum_entry,
	ctf_enum_entry_value,
	value)

_CTF_SET_PROPERTY_IMPL(
	ctf_enum_entry_set_value,
	ctf_enum_entry,
	ctf_enum_entry_value,
	value)

size_t
ctf_enum_entry_memory_usage (ctf_enum_entry enum_entry)
{
	size_t usage = 0;

	usage += CTF_ENUM_ENTRY_SIZE;
	usage += strlen(enum_entry->name);

	return usage;
}

