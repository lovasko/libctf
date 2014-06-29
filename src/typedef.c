#include "typedef.h"

_CTF_GET_PROPERTY_IMPL(ctf_typedef_get_name, struct ctf_typedef*, char*, name)
_CTF_GET_PROPERTY_IMPL(ctf_typedef_get_type, struct ctf_typedef*, 
    struct ctf_type*, type)

