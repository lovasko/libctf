#include "type/int.h"

_CTF_GET_PROPERTY_IMPL(
	ctf_int_get_name,
	ctf_int,
	char*,
	name)

_CTF_SET_PROPERTY_IMPL(
	ctf_int_set_name,
	ctf_int,
	char*,
	name)

_CTF_GET_PROPERTY_IMPL(
	ctf_int_get_size,
	ctf_int,
	ctf_int_size,
	size)

_CTF_SET_PROPERTY_IMPL(
	ctf_int_set_size,
	ctf_int,
	ctf_int_size,
	size)

_CTF_GET_PROPERTY_IMPL(
	ctf_int_get_offset,
	ctf_int,
	ctf_int_offset,
	offset)

_CTF_SET_PROPERTY_IMPL(
	ctf_int_set_offset,
	ctf_int,
	ctf_int_offset,
	offset)

_CTF_GET_PROPERTY_IMPL(
	ctf_int_get_content,
	ctf_int,
	ctf_int_content,
	content)

_CTF_SET_PROPERTY_IMPL(
	ctf_int_set_content,
	ctf_int,
	ctf_int_content,
	content)

_CTF_GET_PROPERTY_IMPL(
	ctf_int_get_is_signed,
	ctf_int,
	uint8_t,
	is_signed)

_CTF_SET_PROPERTY_IMPL(
	ctf_int_set_is_signed,
	ctf_int,
	uint8_t,
	is_signed)

_CTF_FROM_TYPE_IMPL(
	ctf_int_init,
	ctf_int)

_CTF_CREATE_IMPL(
	ctf_int_create,
	ctf_int,
	CTF_INT_SIZE)

const char*
ctf_int_content_to_string (ctf_int_content int_content)
{
	if (int_content == CTF_INT_CONTENT_NUMBER)
		return "number";

	if (int_content == CTF_INT_CONTENT_CHAR)
		return "char";

	if (int_content == CTF_INT_CONTENT_BOOLEAN)
		return "boolean";

	if (int_content == CTF_INT_CONTENT_VARARGS)
		return "varargs";

	return "unknown";
}

