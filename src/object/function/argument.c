#include "object/function/argument.h"

_CTF_GET_PROPERTY_IMPL(
	ctf_argument_get_type, 
	ctf_argument, 
	ctf_type, 
	type)

_CTF_SET_PROPERTY_IMPL(
	ctf_argument_set_type, 
	ctf_argument, 
	ctf_type, 
	type)

size_t
ctf_argument_memory_usage (ctf_argument argument)
{
	(void) argument;

	return CTF_ARGUMENT_SIZE;
}

