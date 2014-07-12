#ifndef CTF_ARRAY_H
#define CTF_ARRAY_H

#include "type.h"
#include "util/property.h"

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

/**
 * Array vardata.
 *
 * We do not convert the index_type from the binary reflection. Name of the
 * array is saved in the parent ctf_type, as this struct is stored in the data
 * field of the ctf_type.
 */
struct ctf_array
{
	char* name;	
	uint32_t element_count; /**< element count */
	union
	{
		ctf_type type; /**< type of the array content */
		uint16_t type_reference;
	};
};
#define CTF_ARRAY_SIZE sizeof(struct ctf_array)

_CTF_GET_PROPERTY_PROTO(ctf_array_get_name, struct ctf_array*, char*)
_CTF_GET_PROPERTY_PROTO(ctf_array_get_element_count, struct ctf_array*, 
    uint32_t)
_CTF_GET_PROPERTY_PROTO(ctf_array_get_type, struct ctf_array*, struct ctf_type*)

#endif

