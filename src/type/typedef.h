#ifndef CTF_TYPEDEF_H
#define CTF_TYPEDEF_H

#include "type/type.h"
#include "util/from_type.h"
#include "util/property.h"

#include <stdint.h>

struct ctf_typedef
{
	char* name;
	union
	{
		ctf_type type;
		ctf_id id;
	};
};
#define CTF_TYPEDEF_SIZE sizeof(struct ctf_typedef)

typedef struct ctf_typedef* ctf_typedef;

_CTF_GET_PROPERTY_PROTO(ctf_typedef_get_name, ctf_typedef, char*)
_CTF_GET_PROPERTY_PROTO(ctf_typedef_get_type, ctf_typedef, ctf_type)

_CTF_FROM_TYPE_PROTO(ctf_typedef_init, ctf_typedef)

#endif

