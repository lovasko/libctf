#ifndef CTF_TYPE_H
#define CTF_TYPE_H

#include <stdint.h>

/* if the small_type.size is greater than this, we should use the large_type */
#define CTF_SMALL_TYPE_THRESHOLD 0xfffe

/*
 * The info table
 *
 * The member info from both, the small_ and large_type, is not a single
 * number, but rather 3 separate variables packed into single 16-bit word.
 * Bytes 0-9 represent the vlen. TODO what is the vlen?
 * Byte 10 represents the boolean flag for the attribute root. TODO what is the
 * root?
 * Bytes 11-15 form the kind of the types. The kind constants CTF_KIND can be
 * found inside the kind.h file.
 */

/**
 * Binary reflection of the small type. 
 *
 * Designated for internal use only.
 * Depending on the kind of the type from the info member, we use either size
 * or type. Kind, like pointer, typedef or const, that only refer to another
 * type use the type member. Kinds, like int or struct, use the size member.
 */
struct _ctf_small_type
{
	uint32_t name; /**< reference to the name */
	uint16_t info; /**< see the info table with description above */
	union
	{
		uint16_t size; /**< size of the whole type in bytes (e.g. CTF_KIND_FUNC has
		all the variant data size included in this variable) */
		uint16_t type; /**< reference to another type */
	};
};
#define _CTF_SMALL_TYPE_SIZE sizeof(struct _ctf_small_type)

/**
 * Binary reflection of the small type. 
 *
 * Designated for internal use only.
 * Instead of the union in the small_type, there is no need for the member
 * "type" that refers to another type, since all referring kinds like pointer,
 * typedef or const need only the small_type. Therefore we only skip this byte
 * with the padding member.
 */
struct _ctf_large_type
{
	uint32_t name; /**< @see _ctf_small_type#name */
	uint16_t info /**< @see _ctf_small_type#info */;
	uint16_t padding; /**< padding byte to ignore the union from small_type */
	uint64_t size; /**< @see _ctf_small_type#size */
};
#define _CTF_LARGE_TYPE_SIZE sizeof(struct _ctf_large_type)

#endif
