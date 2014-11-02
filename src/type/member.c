#include "type/member.h"

_CTF_GET_PROPERTY_IMPL(ctf_member_get_name, ctf_member, char*, name)
_CTF_GET_PROPERTY_IMPL(ctf_member_get_type, ctf_member, ctf_type, type)
_CTF_GET_PROPERTY_IMPL(ctf_member_get_offset, ctf_member, ctf_member_offset,
    offset)

