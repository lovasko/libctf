#include "array.h"

_CTF_GET_PROPERTY_IMPL(ctf_array_get_name, ctf_array, char*, name)
_CTF_GET_PROPERTY_IMPL(ctf_array_get_length, ctf_array, ctf_array_length, 
    length)
_CTF_GET_PROPERTY_IMPL(ctf_array_get_content_type, ctf_array, ctf_type, 
    content_type)

