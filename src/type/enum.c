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

_CTF_LISTING_IMPL(
	ctf_enum_get_next_enum_entry,
	ctf_enum,
	ctf_enum_entry,
	enum_head,
	entries)

_CTF_FROM_TYPE_IMPL(
	ctf_enum_init,
	ctf_enum)

_CTF_CREATE_IMPL(
	ctf_enum_create,
	ctf_enum,
	CTF_ENUM_SIZE)

