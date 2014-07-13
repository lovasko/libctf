#include "float.h"

_CTF_GET_PROPERTY_IMPL(ctf_float_get_name, ctf_float, char*, name)
_CTF_GET_PROPERTY_IMPL(ctf_float_get_size, ctf_float, ctf_float_size, size)
_CTF_GET_PROPERTY_IMPL(ctf_float_get_offset, ctf_float, ctf_float_offset, 
    offset)
_CTF_GET_PROPERTY_IMPL(ctf_float_get_encoding, ctf_float, 
    ctf_float_encoding, encoding)

