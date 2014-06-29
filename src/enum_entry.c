#include "enum_entry.h"

_CTF_GET_PROPERTY_IMPL(ctf_enum_entry_get_name, struct ctf_enum_entry*, char*,
    name)
_CTF_GET_PROPERTY_IMPL(ctf_enum_entry_get_value, struct ctf_enum_entry*,
    int32_t, value)

