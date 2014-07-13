#include "int.h"

_CTF_GET_PROPERTY_IMPL(ctf_int_get_name, ctf_int, char*, name)
_CTF_GET_PROPERTY_IMPL(ctf_int_get_size, ctf_int, ctf_int_size, size)
_CTF_GET_PROPERTY_IMPL(ctf_int_get_offset, ctf_int, ctf_int_offset, offset)
_CTF_GET_PROPERTY_IMPL(ctf_int_get_content, ctf_int, ctf_int_content, content)
_CTF_GET_PROPERTY_IMPL(ctf_int_is_signed, ctf_int, ctf_bool, is_signed)

