#ifndef CTF_ARGUMENT_H
#define CTF_ARGUMENT_H

#include "api/memory_usage.h"
#include "api/property.h"
#include "type/type.h"

/**
 * Function argument.
 *
 * Currently, only the type of the argument is stored, not the name.
 */
struct ctf_argument
{
	union
	{
		ctf_type type; /**< type of the argument */
		ctf_id id; /**< id of the type of the argument */
	};
};
#define CTF_ARGUMENT_SIZE sizeof(struct ctf_argument)

typedef struct ctf_argument* ctf_argument;

_CTF_GET_PROPERTY_PROTO(ctf_argument_get_type, ctf_argument, ctf_type)
_CTF_SET_PROPERTY_PROTO(ctf_argument_set_type, ctf_argument, ctf_type)

_CTF_MEMORY_USAGE_PROTO(ctf_argument_memory_usage, ctf_argument)

#endif

