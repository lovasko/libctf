#ifndef CTF_TYPE_H
#define CTF_TYPE_H

#include "type/kind.h"
#include "util/bool.h"
#include "api/property.h"
#include "api/create.h"

#include <stdint.h>
#include <sys/queue.h>

/* if the small_type.size is greater than this, we should use the large_type */
#define CTF_SMALL_TYPE_THRESHOLD 0xfffe

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
		uint16_t size; /**< size of the whole type in bytes */
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
	uint32_t high_size;
	uint32_t low_size;
};
#define _CTF_LARGE_TYPE_SIZE sizeof(struct _ctf_large_type)

typedef uint16_t ctf_id;
#define CTF_ID_MIN     1
#define CTF_ID_MAX 65536

/**
 * General type information.
 */
struct ctf_type
{
	uint8_t is_root;
	ctf_kind kind; /**< kind of the type, one of the CTF_KIND constants */
	ctf_id id;
	union
	{
		void* data; /**< vardata for complex types and pointer to referenced type in
		case of the reference types. this type should be  */
		ctf_id data_id;
	};

	TAILQ_ENTRY(ctf_type) types; /**< pointer to following types */
};
#define CTF_TYPE_SIZE sizeof(struct ctf_type)

typedef struct ctf_type* ctf_type;

TAILQ_HEAD(ctf_type_head, ctf_type);
#define CTF_TYPE_HEAD_SIZE sizeof(struct ctf_type_head)

_CTF_GET_PROPERTY_PROTO(ctf_type_get_kind, ctf_type, ctf_kind)
_CTF_SET_PROPERTY_PROTO(ctf_type_set_kind, ctf_type, ctf_kind)

_CTF_GET_PROPERTY_PROTO(ctf_type_get_id, ctf_type, ctf_id)
_CTF_SET_PROPERTY_PROTO(ctf_type_set_id, ctf_type, ctf_id)

_CTF_GET_PROPERTY_PROTO(ctf_type_get_is_root, ctf_type, uint8_t)
_CTF_SET_PROPERTY_PROTO(ctf_type_set_is_root, ctf_type, ctf_bool)

_CTF_SET_PROPERTY_PROTO(ctf_type_set_data, ctf_type, void*)

_CTF_CREATE_PROTO(ctf_type_create, ctf_type)

/* HACK
 * This is exactly the same as the FROM_TYPE macro output, but it causes some
 * compilation problems due to the fact that the from_type.h includes type.h
 */
int 
ctf_type_init(ctf_type type, ctf_type* out);

int
ctf_type_to_string(ctf_type type, char** string);

#endif

