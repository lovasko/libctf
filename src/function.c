#include "function.h"

_CTF_GET_PROPERTY_IMPL(ctf_function_get_name, ctf_function, char*, name)
_CTF_GET_PROPERTY_IMPL(ctf_function_get_return_type, ctf_function, ctf_type,
    return_type)
	
_CTF_LISTING_IMPL(ctf_function_get_next_argument, ctf_function, 
    ctf_argument, argument_head, arguments)

_CTF_FROM_TYPE_IMPL(ctf_function_init, ctf_function)

