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

_CTF_GET_PROPERTY_IMPL(
	ctf_enum_get_enum_entry_count,
	ctf_enum,
	ctf_count,
	enum_entry_count)

_CTF_LISTING_IMPL(
	ctf_enum_get_next_enum_entry,
	ctf_enum,
	ctf_enum_entry,
	enum_head,
	entries)

_CTF_FOREACH_IMPL(
	ctf_enum_foreach_enum_entry,
	ctf_enum,
	ctf_enum_entry,
	ctf_enum_get_next_enum_entry)

_CTF_ADD_IMPL(
	ctf_enum_add_enum_entry,
	ctf_enum,
	ctf_enum_entry,
	enum_head,
	entries,
	enum_entry_count)

_CTF_FROM_TYPE_IMPL(
	ctf_enum_init,
	ctf_enum)

_CTF_CREATE_IMPL(
	ctf_enum_create,
	ctf_enum,
	CTF_ENUM_SIZE)

size_t
ctf_enum_memory_usage (ctf_enum _enum)
{
	size_t usage = 0;

	usage += CTF_ENUM_SIZE;
	usage += strlen(_enum->name);

	ctf_enum_entry runner;
	TAILQ_FOREACH (runner, _enum->enum_head, entries)
	{
		usage += ctf_enum_entry_memory_usage(runner);
	}

	return usage;
}

