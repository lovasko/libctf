#ifndef CTF_POINTER_H
#define CTF_POINTER_H

#include <sys/stdint.h>

#include "api/create.h"
#include "api/from_type.h"
#include "api/memory_usage.h"
#include "api/property.h"
#include "type/type.h"

/**
 * Pointer.
 */
struct ctf_pointer
{
	union
	{
		ctf_type type; /**< reference type */
		ctf_id id; /**< reference type id*/
	};
};
#define CTF_POINTER_SIZE sizeof(struct ctf_pointer)

typedef struct ctf_pointer* ctf_pointer;

_CTF_GET_PROPERTY_PROTO(ctf_pointer_get_type, ctf_pointer, ctf_type)
_CTF_SET_PROPERTY_PROTO(ctf_pointer_set_type, ctf_pointer, ctf_type)

_CTF_MEMORY_USAGE_PROTO(ctf_pointer_memory_usage, ctf_pointer)

_CTF_FROM_TYPE_PROTO(ctf_pointer_init, ctf_pointer)
_CTF_CREATE_PROTO(ctf_pointer_create, ctf_pointer)

#endif

