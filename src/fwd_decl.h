#ifndef CTF_FWD_DECL_H
#define CTF_FWD_DECL_H

#include "util/property.h"

#include <stdint.h>

struct ctf_fwd_decl
{
	char* name;
	uint8_t kind;
};
#define CTF_FWD_DECL_SIZE sizeof(struct ctf_fwd_decl)

_CTF_GET_PROPERTY_PROTO(ctf_fwd_decl_get_name, struct ctf_fwd_decl*, char*)
_CTF_GET_PROPERTY_PROTO(ctf_fwd_decl_get_kind, struct ctf_fwd_decl*, uint8_t)

#endif
