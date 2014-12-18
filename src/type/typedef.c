#include "type/typedef.h"

_CTF_GET_PROPERTY_IMPL(
	ctf_typedef_get_name,
	ctf_typedef,
	char*,
	name)

_CTF_SET_PROPERTY_IMPL(
	ctf_typedef_set_name,
	ctf_typedef,
	char*,
	name)

_CTF_GET_PROPERTY_IMPL(
	ctf_typedef_get_type,
	ctf_typedef,
	ctf_type,
	type)

_CTF_SET_PROPERTY_IMPL(
	ctf_typedef_set_type,
	ctf_typedef,
	ctf_type,
	type)

_CTF_FROM_TYPE_IMPL(
	ctf_typedef_init,
	ctf_typedef)

_CTF_CREATE_IMPL(
	ctf_typedef_create,
	ctf_typedef,
	CTF_TYPEDEF_SIZE)

