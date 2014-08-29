#include "type.h"
#include "util/from_type.h"

_CTF_GET_PROPERTY_IMPL(ctf_type_get_kind, ctf_type, ctf_kind, kind)
_CTF_GET_PROPERTY_IMPL(ctf_type_get_id, ctf_type, ctf_id, id)
_CTF_GET_PROPERTY_IMPL(ctf_type_is_root, ctf_type, ctf_bool, is_root)

_CTF_FROM_TYPE_IMPL(ctf_type_init, ctf_type)

