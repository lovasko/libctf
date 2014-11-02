#ifndef CTF_POINTER_H
#define CTF_POINTER_H

#include "type/type.h"
#include "util/from_type.h"
#include "util/property.h"

#include <sys/stdint.h>

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

_CTF_FROM_TYPE_PROTO(ctf_pointer_init, ctf_pointer)

#endif

