#ifndef CTF_ENUM_H
#define CTF_ENUM_H

#include "enum_entry.h"
#include "util/property.h"
#include "util/listing.h"

#include <stdint.h>
#include <sys/queue.h>

struct ctf_enum
{
	char *name;
	struct ctf_enum_head *enum_head;
};
#define CTF_ENUM_SIZE sizeof(struct ctf_enum)

_CTF_GET_PROPERTY_PROTO(ctf_enum_get_name, struct ctf_enum*, char*)

_CTF_LISTING_PROTO(ctf_enum_get_next_enum_entry, struct ctf_enum*, 
    struct ctf_enum_entry*)


#endif

