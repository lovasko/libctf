#ifndef CTF_ARGUMENT_H
#define CTF_ARGUMENT_H

#include "type.h"
#include "util/property.h"

#include <sys/queue.h>

/**
 * Function argument.
 *
 * Currently, only the type of the argument is stored, not the name.
 */
struct ctf_argument
{
	union
	{
		ctf_type type; /**< type of the argument */
		uint16_t type_reference;
	};

	TAILQ_ENTRY(ctf_argument) arguments; /**< pointer to following arguments */
};
#define CTF_ARGUMENT_SIZE sizeof(struct ctf_argument)

typedef struct ctf_argument* ctf_argument;

TAILQ_HEAD(ctf_argument_head, ctf_argument);
#define CTF_ARGUMENT_HEAD_SIZE sizeof(struct ctf_argument_head)

_CTF_GET_PROPERTY_PROTO(ctf_argument_get_type, ctf_argument, ctf_type)

#endif

