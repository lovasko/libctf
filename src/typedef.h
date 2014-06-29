#ifndef CTF_TYPEDEF_H
#define CTF_TYPEDEF_H

#include "type.h"
#include "util/property.h"

#include <stdint.h>

struct ctf_typedef
{
	char *name;
	union
	{
		struct ctf_type *type;
		uint16_t type_reference;
	};
};
#define CTF_TYPEDEF_SIZE sizeof(struct ctf_typedef)

_CTF_GET_PROPERTY_PROTO(ctf_typedef_get_name, struct ctf_typedef*, char*)
_CTF_GET_PROPERTY_PROTO(ctf_typedef_get_type, struct ctf_typedef*, 
    struct ctf_type*)

#endif

