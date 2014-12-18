#include "type/fwd_decl.h"

_CTF_GET_PROPERTY_IMPL(
	ctf_fwd_decl_get_name,
	ctf_fwd_decl,
	char*,
	name)

_CTF_SET_PROPERTY_IMPL(
	ctf_fwd_decl_set_name,
	ctf_fwd_decl,
	char*,
	name)

_CTF_GET_PROPERTY_IMPL(
	ctf_fwd_decl_get_kind,
	ctf_fwd_decl,
	ctf_kind,
	kind)

_CTF_SET_PROPERTY_IMPL(
	ctf_fwd_decl_set_kind,
	ctf_fwd_decl,
	ctf_kind,
	kind)

_CTF_FROM_TYPE_IMPL(
	ctf_fwd_decl_init,
	ctf_fwd_decl)

_CTF_CREATE_IMPL(
	ctf_fwd_decl_create,
	ctf_fwd_decl,
	CTF_FWD_DECL_SIZE)

