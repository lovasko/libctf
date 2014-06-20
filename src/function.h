#ifndef CTF_FUNCTION_H
#define CTF_FUNCTION_H

#include "type.h"
#include "argument.h"

#include <stdint.h>
#include <sys/queue.h>

/**
 * Function vardata.
 */
struct ctf_function
{
	char *name;
	union
	{
		struct ctf_type *return_type; /**< return type of the function */
		uint16_t return_type_reference;
	};
	struct ctf_argument_head *argument_head; /**< linked list of arguments */

	TAILQ_ENTRY(ctf_function) functions;
};
#define CTF_FUNCTION_SIZE sizeof(struct ctf_function)

TAILQ_HEAD(ctf_function_head, ctf_function);
#define CTF_FUNCTION_HEAD_SIZE sizeof(struct ctf_function_head)

#endif

