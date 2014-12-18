#ifndef CTF_MEMBER_H
#define CTF_MEMBER_H

#include "type/type.h"
#include "util/property.h"
#include "util/create.h"

#include <stdint.h>
#include <sys/queue.h>

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
	uint32_t high_offset;
	uint32_t low_offset;
};
#define _CTF_LARGE_MEMBER_SIZE sizeof(struct _ctf_large_member)

typedef uint64_t ctf_member_offset;
#define CTF_MEMBER_OFFSET_MIN                     0
#define CTF_MEMBER_OFFSET_MAX 0xffffffffffffffffULL

/**
 * Struct or union member.
 */
struct ctf_member
{
	char* name; /**< name of the member */
	union
	{
		ctf_type type; /**< type of the member */
		ctf_id id;
	};
	ctf_member_offset offset; /**< offset inside the struct 
	    (union, by the language design, has all offsets 0) */

	TAILQ_ENTRY(ctf_member) members; /**< pointer to following members */
};
#define CTF_MEMBER_SIZE sizeof(struct ctf_member)

typedef struct ctf_member* ctf_member;

TAILQ_HEAD(ctf_member_head, ctf_member);
#define CTF_MEMBER_HEAD_SIZE sizeof(struct ctf_member_head)

_CTF_GET_PROPERTY_PROTO(ctf_member_get_name, ctf_member, char*)
_CTF_SET_PROPERTY_PROTO(ctf_member_set_name, ctf_member, char*)

_CTF_GET_PROPERTY_PROTO(ctf_member_get_type, ctf_member, ctf_type)
_CTF_SET_PROPERTY_PROTO(ctf_member_set_type, ctf_member, ctf_type)

_CTF_GET_PROPERTY_PROTO(ctf_member_get_offset, ctf_member, ctf_member_offset)
_CTF_SET_PROPERTY_PROTO(ctf_member_set_offset, ctf_member, ctf_member_offset)

_CTF_CREATE_PROTO(ctf_member_create, ctf_member)

#endif

