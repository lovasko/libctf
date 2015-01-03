#ifndef CTF_ARRAY_H
#define CTF_ARRAY_H

#include "type/type.h"
#include "api/property.h"
#include "api/from_type.h"
#include "api/create.h"
#include "api/memory_usage.h"

#include <stdint.h>

/**
 * Binary reflection of an array.
 *
 * Designated for internal use only.
 */
struct _ctf_array
{
	uint16_t content_type; /**< reference to the type of the contents */
	uint16_t index_type; /**< reference to the type of the index TODO why is this
	here? is it not always an integer?*/
	uint32_t element_count; /**< number of elements */
};
#define _CTF_ARRAY_SIZE sizeof(struct _ctf_array)

typedef uint32_t ctf_array_length;
#define CTF_ARRAY_LENGTH_MIN          0
#define CTF_ARRAY_LENGTH_MAX 0xffffffff

/**
 * Array.
 *
 * We do not store the index_type from the binary reflection. The indexation is
 * expected to be always of an integral type.
 */
struct ctf_array
{
	ctf_array_length length;
	union
	{
		ctf_type content_type; /**< type of the array content */
		ctf_id content_id;
	};
};
#define CTF_ARRAY_SIZE sizeof(struct ctf_array)

typedef struct ctf_array* ctf_array;

_CTF_GET_PROPERTY_PROTO(ctf_array_get_length, ctf_array, ctf_array_length)
_CTF_SET_PROPERTY_PROTO(ctf_array_set_length, ctf_array, ctf_array_length)

_CTF_GET_PROPERTY_PROTO(ctf_array_get_content_type, ctf_array, ctf_type)
_CTF_SET_PROPERTY_PROTO(ctf_array_set_content_type, ctf_array, ctf_type)

_CTF_MEMORY_USAGE_PROTO(ctf_array_memory_usage, ctf_array)

_CTF_CREATE_PROTO(ctf_array_create, ctf_array)
_CTF_FROM_TYPE_PROTO(ctf_array_init, ctf_array)

#endif

