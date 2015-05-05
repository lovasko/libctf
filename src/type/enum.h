#ifndef CTF_ENUM_H
#define CTF_ENUM_H

#include <sys/stdint.h>
#include <sys/queue.h>

#include "api/add.h"
#include "api/create.h"
#include "api/foreach.h"
#include "api/from_type.h"
#include "api/listing.h"
#include "api/memory_usage.h"
#include "api/property.h"
#include "type/enum_entry.h"
#include "util/count.h"

/**
 * Enum.
 */
struct ctf_enum
{
	char* name; /*< name of the enum */
	ctf_count enum_entry_count;
	struct ctf_enum_head* enum_head;
};
#define CTF_ENUM_SIZE sizeof(struct ctf_enum)

typedef struct ctf_enum* ctf_enum;

_CTF_GET_PROPERTY_PROTO(ctf_enum_get_name, ctf_enum, char*)
_CTF_SET_PROPERTY_PROTO(ctf_enum_set_name, ctf_enum, char*)

_CTF_GET_PROPERTY_PROTO(ctf_enum_get_enum_entry_count, ctf_enum, ctf_count)
_CTF_LISTING_PROTO(ctf_enum_get_next_enum_entry, ctf_enum, ctf_enum_entry)
_CTF_FOREACH_PROTO(ctf_enum_foreach_enum_entry, ctf_enum, ctf_enum_entry)
_CTF_ADD_PROTO(ctf_enum_add_enum_entry, ctf_enum, ctf_enum_entry)

_CTF_MEMORY_USAGE_PROTO(ctf_enum_memory_usage, ctf_enum)

_CTF_FROM_TYPE_PROTO(ctf_enum_init, ctf_enum)
_CTF_CREATE_PROTO(ctf_enum_create, ctf_enum)

#endif

