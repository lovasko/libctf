#ifndef CTF_ENUM_ENTRY_H
#define CTF_ENUM_ENTRY_H

#include "api/property.h"
#include "api/memory_usage.h"

#include <stdint.h>
#include <sys/queue.h>

/**
 * Binary reflection of the enum variant data.
 *
 * Designated for internal use only.
 */
struct _ctf_enum_entry
{
	uint32_t name; /**< name of the enum element */
	int32_t value; /**< value associated with this element */
};
#define _CTF_ENUM_ENTRY_SIZE sizeof(struct _ctf_enum_entry)

typedef int32_t ctf_enum_entry_value;
#define CTF_ENUM_ENTRY_VALUE_MIN (-0x7fffffff - 1)
#define CTF_ENUM_ENTRY_VALUE_MAX        0x7fffffff

/**
 * Enum entry.
 */
struct ctf_enum_entry
{
	char* name; /**< name of the entry */
	ctf_enum_entry_value value; /**< value of the entry */

	TAILQ_ENTRY(ctf_enum_entry) entries;
};
#define CTF_ENUM_ENTRY_SIZE sizeof(struct ctf_enum_entry)

typedef struct ctf_enum_entry* ctf_enum_entry;

TAILQ_HEAD(ctf_enum_head, ctf_enum_entry);
#define CTF_ENUM_HEAD_SIZE sizeof(struct ctf_enum_head)

_CTF_GET_PROPERTY_PROTO(ctf_enum_entry_get_name, ctf_enum_entry, char*)
_CTF_SET_PROPERTY_PROTO(ctf_enum_entry_set_name, ctf_enum_entry, char*)

_CTF_GET_PROPERTY_PROTO(ctf_enum_entry_get_value, ctf_enum_entry, 
    ctf_enum_entry_value)
_CTF_SET_PROPERTY_PROTO(ctf_enum_entry_set_value, ctf_enum_entry,
    ctf_enum_entry_value)

_CTF_MEMORY_USAGE_PROTO(ctf_enum_entry_memory_usage, ctf_enum_entry)

#endif

