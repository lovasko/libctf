#include "type/fwd_decl.h"

_CTF_GET_PROPERTY_IMPL(ctf_fwd_decl_get_name, ctf_fwd_decl, char*, name)
_CTF_GET_PROPERTY_IMPL(ctf_fwd_decl_get_kind, ctf_fwd_decl, ctf_kind, kind)

_CTF_FROM_TYPE_IMPL(ctf_fwd_decl_init, ctf_fwd_decl)
