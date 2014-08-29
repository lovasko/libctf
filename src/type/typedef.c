#include "typedef.h"

_CTF_GET_PROPERTY_IMPL(ctf_typedef_get_name, ctf_typedef, char*, name)
_CTF_GET_PROPERTY_IMPL(ctf_typedef_get_type, ctf_typedef, ctf_type, type)

_CTF_FROM_TYPE_IMPL(ctf_typedef_init, ctf_typedef)

