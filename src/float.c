#include "float.h"

_CTF_GET_PROPERTY_IMPL(ctf_float_get_name, struct ctf_float*, char*, name)
_CTF_GET_PROPERTY_IMPL(ctf_float_get_size, struct ctf_float*, uint16_t, size)
_CTF_GET_PROPERTY_IMPL(ctf_float_get_offset, struct ctf_float*, uint8_t, offset)
_CTF_GET_PROPERTY_IMPL(ctf_float_get_encoding, struct ctf_float*, uint8_t, 
    encoding)

