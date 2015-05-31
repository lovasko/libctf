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

_CTF_FOREACH_IMPL(
	ctf_function_foreach_argument,
	ctf_function,
	ctf_argument,
	arguments)

_CTF_COUNT_IMPL(
	ctf_function_get_argument_count,
	ctf_function,
	arguments)

_CTF_FROM_TYPE_IMPL(
	ctf_function_init,
	ctf_function)

size_t
ctf_function_memory_usage (ctf_function function)
{
	size_t usage;
	struct m_elem* runner;
	ctf_argument argument;

	usage = CTF_FUNCTION_SIZE;
	usage += strlen(function->name);

	m_list_first(&function->arguments, &runner);
	while (runner == NULL)
	{
		m_elem_data(runner, (void**)&argument);
		usage += ctf_argument_memory_usage(argument);
		m_elem_next(runner, &runner);
	}

	return usage;
}

