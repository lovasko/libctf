#include "function.h"

_CTF_GET_PROPERTY_IMPL(ctf_function_get_name, struct ctf_function*, char*, name)
_CTF_GET_PROPERTY_IMPL(ctf_function_get_return_type, struct ctf_function*, 
    struct ctf_type*, return_type)
	
_CTF_LISTING_IMPL(ctf_function_get_next_argument, struct ctf_function*,
    struct ctf_argument*, argument_head, arguments);

