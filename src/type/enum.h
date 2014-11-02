#ifndef CTF_ENUM_H
#define CTF_ENUM_H

#include "type/enum_entry.h"
#include "util/from_type.h"
#include "util/listing.h"
#include "util/property.h"

#include <stdint.h>
#include <sys/queue.h>

/**
 * Enum.
 */
struct ctf_enum
{
	char* name /*< name of the enum */;

	struct ctf_enum_head* enum_head;
};
#define CTF_ENUM_SIZE sizeof(struct ctf_enum)

typedef struct ctf_enum* ctf_enum;

_CTF_GET_PROPERTY_PROTO(ctf_enum_get_name, ctf_enum, char*)

_CTF_LISTING_PROTO(ctf_enum_get_next_enum_entry, ctf_enum, ctf_enum_entry)

_CTF_FROM_TYPE_PROTO(ctf_enum_init, ctf_enum)

#endif

