#ifndef CTF_POINTER_H
#define CTF_POINTER_H

#include "type.h"
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
	uint8_t attributes; /**< bitfield of attributes */
};
#define CTF_POINTER_SIZE sizeof(struct ctf_pointer)

typedef struct ctf_pointer* ctf_pointer;

#endif

