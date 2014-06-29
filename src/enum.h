#ifndef CTF_ENUM_H
#define CTF_ENUM_H

#include "enum_entry.h"

#include <stdint.h>
#include <sys/queue.h>

struct ctf_enum
{
	char *name;
	struct ctf_enum_head *enum_head;
};
#define CTF_ENUM_SIZE sizeof(struct ctf_enum)

int
ctf_enum_get_name (struct ctf_enum *_enum, char **out_name);

int
ctf_enum_get_next_enum_entry (struct ctf_enum *_enum, 
    struct ctf_enum_entry *enum_entry, struct ctf_enum_entry **out_enum_entry);

#endif

