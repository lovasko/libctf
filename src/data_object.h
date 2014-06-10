#ifndef CTF_DATA_OBJECT_H
#define CTF_DATA_OBJECT_H

#include "type.h"

#include <sys/queue.h>

struct ctf_data_object
{
	char *name;
	struct ctf_type *type;

	LIST_ENTRY(ctf_data_object) data_objects;
};
#define CTF_DATA_OBJECT_SIZE sizeof(struct ctf_data_object)

LIST_HEAD(ctf_data_object_head, ctf_data_object);
#define CTF_DATA_OBJECT_HEAD_SIZE sizeof(struct ctf_data_object_head)

#endif

