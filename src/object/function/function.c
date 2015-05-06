#include "object/function/function.h"

_CTF_GET_PROPERTY_IMPL(
	ctf_function_get_name,
	ctf_function,
	char*,
	name)

_CTF_SET_PROPERTY_IMPL(
	ctf_function_set_name,
	ctf_function,
	char*,
	name)

_CTF_GET_PROPERTY_IMPL(
	ctf_function_get_return_type,
	ctf_function,
	ctf_type,
	return_type)

_CTF_SET_PROPERTY_IMPL(
	ctf_function_set_return_type,
	ctf_function,
	ctf_type,
	return_type)

_CTF_LISTING_IMPL(
	ctf_function_get_next_argument,
	ctf_function, 
	ctf_argument,
	argument_head,
	arguments)

_CTF_FOREACH_IMPL(
	ctf_function_foreach_argument,
	ctf_function,
	ctf_argument,
	ctf_function_get_next_argument)

_CTF_FROM_TYPE_IMPL(
	ctf_function_init,
	ctf_function)

size_t
ctf_function_memory_usage (ctf_function function)
{
	size_t usage = 0;

	usage += CTF_FUNCTION_SIZE;
	usage += strlen(function->name);

	ctf_argument runner;
	TAILQ_FOREACH (runner, function->argument_head, arguments)
	{
		usage += ctf_argument_memory_usage(runner);
	}

	return usage;
}

