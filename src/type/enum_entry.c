#include "type/enum_entry.h"

_CTF_GET_PROPERTY_IMPL(ctf_enum_entry_get_name, ctf_enum_entry, char*, name)
_CTF_GET_PROPERTY_IMPL(ctf_enum_entry_get_value, ctf_enum_entry, 
    ctf_enum_entry_value, value)

