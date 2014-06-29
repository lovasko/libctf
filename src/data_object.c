#include "data_object.h"

_CTF_GET_PROPERTY_IMPL(ctf_data_object_get_name, struct ctf_data_object*, char*,
    name)
_CTF_GET_PROPERTY_IMPL(ctf_data_object_get_type, struct ctf_data_object*,
    struct ctf_type*, type)

