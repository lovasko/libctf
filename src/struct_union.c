#include "struct_union.h"

_CTF_GET_PROPERTY_IMPL(ctf_struct_union_get_name, ctf_struct_union, char*, 
    name)

_CTF_LISTING_IMPL(ctf_struct_union_get_next_member, ctf_struct_union,
    ctf_member, member_head, members)

_CTF_FROM_TYPE_IMPL(ctf_struct_union_init, ctf_struct_union)

