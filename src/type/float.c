#include "type/float.h"

_CTF_GET_PROPERTY_IMPL(
	ctf_float_get_name,
	ctf_float,
	char*,
	name)

_CTF_SET_PROPERTY_IMPL(
	ctf_float_set_name,
	ctf_float,
	char*,
	name)

_CTF_GET_PROPERTY_IMPL(
	ctf_float_get_size,
	ctf_float,
	ctf_float_size,
	size)

_CTF_SET_PROPERTY_IMPL(
	ctf_float_set_size,
	ctf_float,
	ctf_float_size,
	size)

_CTF_GET_PROPERTY_IMPL(
	ctf_float_get_offset,
	ctf_float,
	ctf_float_offset,
	offset)

_CTF_SET_PROPERTY_IMPL(
	ctf_float_set_offset,
	ctf_float,
	ctf_float_offset,
	offset)

_CTF_GET_PROPERTY_IMPL(
	ctf_float_get_encoding,
	ctf_float,
	ctf_float_encoding,
	encoding)

_CTF_SET_PROPERTY_IMPL(
	ctf_float_set_encoding,
	ctf_float,
	ctf_float_encoding,
	encoding)

_CTF_CREATE_IMPL(
	ctf_float_create,
	ctf_float,
	CTF_FLOAT_SIZE)

_CTF_FROM_TYPE_IMPL(
	ctf_float_init,
	ctf_float)

const char*
ctf_float_encoding_to_string (ctf_float_encoding float_encoding)
{
	static const char* translation_table[] = 
	{
		"float:none", 
		"single", 
		"double", 
		"complex",
		"double complex",
		"long double complex", 
		"long double", 
		"interval", 
		"double interval", 
		"long double interval", 
		"imaginary",
		"double imaginary",
		"long double imaginary"
	};

	if (float_encoding <= CTF_FLOAT_ENCODING_MAX 
	 && float_encoding >= CTF_FLOAT_ENCODING_MIN)
		return translation_table[float_encoding];
	else
		return "unresolvable";
}

