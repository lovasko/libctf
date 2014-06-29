#include "array.h"

_CTF_GET_PROPERTY_IMPL(ctf_array_get_name, struct ctf_array*, char*, name)
_CTF_GET_PROPERTY_IMPL(ctf_array_get_element_count, struct ctf_array*, uint32_t, 
    element_count)
_CTF_GET_PROPERTY_IMPL(ctf_array_get_type, struct ctf_array*, struct ctf_type*, 
    type)

