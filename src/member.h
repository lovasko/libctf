#ifndef CTF_MEMBER_H
#define CTF_MEMBER_H

#include <stdint.h>

/* 
 * If size member of the small_/large_type is above this threshold, all members
 * of this struct/union are large_members. Otherwise, all are small_members.
 */
#define CTF_MEMBER_THRESHOLD 8192

/**
 * Binary reflection of the small struct/union member.
 *
 * Designated for internal use only.
 */
struct _ctf_small_member
{
	uint32_t name; /**< reference to the name */
	uint16_t type; /**< reference to the type */
	uint16_t offset; /**< offset from the beginning of the struct (since in the
	union everything has offset 0 by design) */
};
#define _CTF_SMALL_MEMBER_SIZE sizeof(struct _ctf_small_member)

/**
 * Binary reflection of the large struct/union member.
 *
 * Designated for internal use only.
 */
struct _ctf_large_member
{
	uint32_t name; /**< @see _ctf_small_member#name */
	uint16_t type; /**< @see _ctf_small_member#type */
	uint16_t padding; /**< pure padding purposes */
	uint64_t offset; /**< @see _ctf_small_member#offset */
};
#define _CTF_LARGE_MEMBER_SIZE sizeof(struct _ctf_large_member)

/**
 * Struct or union member.
 */
struct ctf_member
{
	char *name; /**< name of the member */
	struct ctf_type *type; /**< type of the member */
	uint64_t offset; /**< offset inside the struct (union, by design, has all
	offsets 0) */

	LIST_ENTRY(ctf_member) members; /**< pointer to following members */
};
#define CTF_MEMBER_SIZE sizeof(struct ctf_member)

LIST_HEAD(ctf_member_head, ctf_member);
#define CTF_MEMBER_HEAD_SIZE sizeof(struct ctf_member_head)

#endif

