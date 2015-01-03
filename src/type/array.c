#include "type/array.h"

/* length */
_CTF_GET_PROPERTY_IMPL(
	ctf_array_get_length, 
	ctf_array, 
	ctf_array_length, 
	length)

_CTF_SET_PROPERTY_IMPL(
	ctf_array_set_length,
	ctf_array,
	ctf_array_length,
	length)


/* content type */
_CTF_GET_PROPERTY_IMPL(
	ctf_array_get_content_type, 
	ctf_array, 
	ctf_type, 
	content_type)

_CTF_SET_PROPERTY_IMPL(
	ctf_array_set_content_type,
	ctf_array,
	ctf_type,
	content_type)


/* from type */
_CTF_FROM_TYPE_IMPL(
	ctf_array_init, 
	ctf_array)


/* create */
_CTF_CREATE_IMPL(
	ctf_array_create,
	ctf_array,
	CTF_ARRAY_SIZE)

size_t
ctf_array_memory_usage (ctf_array array)
{
	(void) array;

	return CTF_ARRAY_SIZE;
}

