#ifndef CTF_FWD_DECL_H
#define CTF_FWD_DECL_H

#include "type/kind.h"
#include "api/from_type.h"
#include "api/property.h"
#include "api/create.h"

#include <stdint.h>

/**
 * Forward declaration.
 */
struct ctf_fwd_decl
{
	char* name;
	ctf_kind kind;
};
#define CTF_FWD_DECL_SIZE sizeof(struct ctf_fwd_decl)

typedef struct ctf_fwd_decl* ctf_fwd_decl;

_CTF_GET_PROPERTY_PROTO(ctf_fwd_decl_get_name, ctf_fwd_decl, char*)
_CTF_SET_PROPERTY_PROTO(ctf_fwd_decl_set_name, ctf_fwd_decl, char*)

_CTF_GET_PROPERTY_PROTO(ctf_fwd_decl_get_kind, ctf_fwd_decl, ctf_kind)
_CTF_SET_PROPERTY_PROTO(ctf_fwd_decl_set_kind, ctf_fwd_decl, ctf_kind)

_CTF_FROM_TYPE_PROTO(ctf_fwd_decl_init, ctf_fwd_decl)
_CTF_CREATE_PROTO(ctf_fwd_decl_create, ctf_fwd_decl)

#endif

