#include "int.h"

_CTF_GET_PROPERTY_IMPL(ctf_int_get_name, struct ctf_int*, char*, name)
_CTF_GET_PROPERTY_IMPL(ctf_int_get_size, struct ctf_int*, uint16_t, size)
_CTF_GET_PROPERTY_IMPL(ctf_int_get_offset, struct ctf_int*, uint8_t, offset)
_CTF_GET_PROPERTY_IMPL(ctf_int_get_content, struct ctf_int*, uint8_t, content)
_CTF_GET_PROPERTY_IMPL(ctf_int_is_signed, struct ctf_int*, int, is_signed)

