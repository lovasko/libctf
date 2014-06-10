#ifndef CTF_FUNCTION_H
#define CTF_FUNCTION_H

#include "type.h"
#include "argument.h"

/**
 * Function vardata.
 */
struct ctf_function
{
	union
	{
		struct ctf_type *return_type; /**< return type of the function */
		uint16_t return_type_reference;
	};
	struct ctf_argument_head *argument_head; /**< linked list of arguments */
};
#define CTF_FUNCTION_SIZE sizeof(struct ctf_function)

#endif

