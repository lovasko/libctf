#ifndef CTF_ENUM_H
#define CTF_ENUM_H

#include <sys/stdint.h>

#include <m_list.h>

#include "api/add.h"
#include "api/create.h"
#include "api/count.h"
#include "api/foreach.h"
#include "api/from_type.h"
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
	struct m_list entries;
};
#define CTF_ENUM_SIZE sizeof(struct ctf_enum)

typedef struct ctf_enum* ctf_enum;

_CTF_GET_PROPERTY_PROTO(ctf_enum_get_name, ctf_enum, char*)
_CTF_SET_PROPERTY_PROTO(ctf_enum_set_name, ctf_enum, char*)

_CTF_FOREACH_PROTO(ctf_enum_foreach_enum_entry, ctf_enum, ctf_enum_entry)
_CTF_COUNT_PROTO(ctf_enum_get_entry_count, ctf_enum)
_CTF_ADD_PROTO(ctf_enum_add_enum_entry, ctf_enum, ctf_enum_entry)

_CTF_MEMORY_USAGE_PROTO(ctf_enum_memory_usage, ctf_enum)

_CTF_FROM_TYPE_PROTO(ctf_enum_init, ctf_enum)
_CTF_CREATE_PROTO(ctf_enum_create, ctf_enum)

#endif

