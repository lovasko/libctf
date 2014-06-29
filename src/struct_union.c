#include "struct_union.h"

_CTF_GET_PROPERTY_IMPL(ctf_struct_union_get_name, struct ctf_struct_union*,
    char*, name)

_CTF_LISTING_IMPL(ctf_struct_union_get_next_member, struct ctf_struct_union*,
    struct ctf_member*, member_head, members)

