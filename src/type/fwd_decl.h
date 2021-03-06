#ifndef CTF_FWD_DECL_H
#define CTF_FWD_DECL_H

#include <sys/stdint.h>

#include "api/create.h"
#include "api/from_type.h"
#include "api/memory_usage.h"
#include "api/property.h"
#include "type/kind.h"

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

_CTF_MEMORY_USAGE_PROTO(ctf_fwd_decl_memory_usage, ctf_fwd_decl)

_CTF_FROM_TYPE_PROTO(ctf_fwd_decl_init, ctf_fwd_decl)
_CTF_CREATE_PROTO(ctf_fwd_decl_create, ctf_fwd_decl)

#endif

