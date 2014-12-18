#include "type/member.h"

_CTF_GET_PROPERTY_IMPL(
	ctf_member_get_name,
	ctf_member,
	char*,
	name)

_CTF_SET_PROPERTY_IMPL(
	ctf_member_set_name,
	ctf_member,
	char*,
	name)

_CTF_GET_PROPERTY_IMPL(
	ctf_member_get_type,
	ctf_member,
	ctf_type,
	type)

_CTF_SET_PROPERTY_IMPL(
	ctf_member_set_type,
	ctf_member,
	ctf_type,
	type)

_CTF_GET_PROPERTY_IMPL(
	ctf_member_get_offset,
	ctf_member,
	ctf_member_offset,
	offset)

_CTF_SET_PROPERTY_IMPL(
	ctf_member_set_offset,
	ctf_member,
	ctf_member_offset,
	offset)

_CTF_CREATE_IMPL(
	ctf_member_create,
	ctf_member,
	CTF_MEMBER_SIZE)

