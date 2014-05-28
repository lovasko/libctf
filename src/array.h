#ifndef CTF_ARRAY_H
#define CTF_ARRAY_H

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

#endif

