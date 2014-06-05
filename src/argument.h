#ifndef CTF_ARGUMENT_H
#define CTF_ARGUMENT_H

#include "type.h"

#include <sys/queue.h>

struct ctf_argument
{
	struct ctf_type *type;

	LIST_ENTRY(ctf_argument) arguments;
};
#define CTF_ARGUMENT_SIZE sizeof(struct ctf_argument)

LIST_HEAD(ctf_argument_head, ctf_argument);
#define CTF_ARGUMENT_HEAD_SIZE sizeof(struct ctf_argument_head)

#endif

