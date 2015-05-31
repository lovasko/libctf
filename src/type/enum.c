#include "type/enum.h"

_CTF_GET_PROPERTY_IMPL(
	ctf_enum_get_name,
	ctf_enum,
	char*,
	name)

_CTF_SET_PROPERTY_IMPL(
	ctf_enum_set_name,
	ctf_enum,
	char*,
	name)

_CTF_FOREACH_IMPL(
	ctf_enum_foreach_enum_entry,
	ctf_enum,
	ctf_enum_entry,
	entries)

_CTF_COUNT_IMPL(
	ctf_enum_get_entry_count,
	ctf_enum,
	entries)

_CTF_ADD_IMPL(
	ctf_enum_add_enum_entry,
	ctf_enum,
	ctf_enum_entry,
	entries)

_CTF_FROM_TYPE_IMPL(
	ctf_enum_init,
	ctf_enum)

_CTF_CREATE_1_LIST_IMPL(
	ctf_enum_create,
	ctf_enum,
	CTF_ENUM_SIZE,
	entries)

size_t
ctf_enum_memory_usage (ctf_enum _enum)
{
	size_t usage;
	struct m_elem* runner;
	ctf_enum_entry entry;

	usage = CTF_ENUM_SIZE;
	usage += strlen(_enum->name);

	m_list_first(&_enum->entries, &runner);
	while (runner != NULL)
	{
		m_elem_data(runner, (void**)&entry);	
		usage += ctf_enum_entry_memory_usage(entry);
		m_elem_next(runner, &runner);
	}

	return usage;
}

