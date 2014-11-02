#include "type/array.h"

_CTF_GET_PROPERTY_IMPL(ctf_array_get_length, ctf_array, ctf_array_length, 
    length)
_CTF_GET_PROPERTY_IMPL(ctf_array_get_content_type, ctf_array, ctf_type, 
    content_type)

_CTF_FROM_TYPE_IMPL(ctf_array_init, ctf_array)

