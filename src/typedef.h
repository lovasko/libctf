#ifndef CTF_TYPEDEF_H
#define CTF_TYPEDEF_H

#include "type.h"

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

int
ctf_typedef_get_name (struct ctf_typedef *_typedef, char **out_name);

int
ctf_typedef_get_type (struct ctf_typedef *_typedef, struct ctf_type **out_type);

#endif

