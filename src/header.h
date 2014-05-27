#ifndef CTF_HEADER_H
#define CTF_HEADER_H

#include <stdint.h>

#define CTF_MAGIC 0xCFF1

#define CTF_COMPRESSED 0x1

/**
 * Binary reflection of the preface of the CTF header.
 *
 * The preface is never compressed or anyhow affected. 
 * Designated for internal use only.
 *
 * Flags:
 * 0x1 = compressed
 */
struct _ctf_preface
{
	uint16_t magic; /**< magic number identifying the format (see CTF_MAGIC) */
	uint8_t version; /**< version indicator */
	uint8_t flags; /**< flags (see the struct description) */
};

/**
 * Binary reflection of the CTF header.
 *
 * Note that all the offsets are starting just after this header. E.g. even
 * though the label_offset is 0, it still means that you have to look at the 0
 * + _CTF_HEADER_SIZE. 
 * Designated for internal use only.
 */
struct _ctf_header
{
	struct _ctf_preface preface; /**< the preface */

	uint32_t parent_label; /**< reference to the parent label */
	uint32_t parent_basename; /**< reference to the parent basename */

	uint32_t label_offset; /**< offset of the label section */
	uint32_t object_offset; /**< offset of the object section */
	uint32_t function_offset; /**< offset of the function section */
	uint32_t type_offset; /**< offset of the type section */

	uint32_t string_offset; /**< offset of the internal string table */
	uint32_t string_length; /**< length of the internal string table */
};
#define _CTF_HEADER_SIZE sizeof(struct _ctf_header)

#endif

