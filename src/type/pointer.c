#include "type/pointer.h"

_CTF_GET_PROPERTY_IMPL(
	ctf_pointer_get_type,
	ctf_pointer,
	ctf_type,
	type)

_CTF_SET_PROPERTY_IMPL(
	ctf_pointer_set_type,
	ctf_pointer,
	ctf_type,
	type)

_CTF_FROM_TYPE_IMPL(
	ctf_pointer_init,
	ctf_pointer)

_CTF_CREATE_IMPL(
	ctf_pointer_create,
	ctf_pointer,
	CTF_POINTER_SIZE)

size_t
ctf_pointer_memory_usage (ctf_pointer pointer)
{
	(void) pointer;

	return CTF_POINTER_SIZE;
}

