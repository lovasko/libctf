#include "enum.h"

_CTF_GET_PROPERTY_IMPL(ctf_enum_get_name, struct ctf_enum*, char*, name)
_CTF_LISTING_IMPL(ctf_enum_get_next_enum_entry, struct ctf_enum*, 
    struct ctf_enum_entry*, enum_head, entries)

