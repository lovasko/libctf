#include "member.h"

_CTF_GET_PROPERTY_IMPL(ctf_member_get_name, struct ctf_member*, char*, name)
_CTF_GET_PROPERTY_IMPL(ctf_member_get_type, struct ctf_member*, 
    struct ctf_type*, type)
_CTF_GET_PROPERTY_IMPL(ctf_member_get_offset, struct ctf_member*, uint64_t, 
    offset)

