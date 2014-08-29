#include "data_object.h"

_CTF_GET_PROPERTY_IMPL(ctf_data_object_get_name, ctf_data_object, char*, name)
_CTF_GET_PROPERTY_IMPL(ctf_data_object_get_type, ctf_data_object, ctf_type, 
    type)

