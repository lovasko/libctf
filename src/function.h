#ifndef CTF_FUNCTION_H
#define CTF_FUNCTION_H

#include "type.h"
#include "argument.h"

/**
 * Function vardata.
 */
struct ctf_function
{
	struct ctf_type *return_type; /**< return type of the function */
	struct ctf_argument_head *argument_head; /**< linked list of arguments */
};
#define CTF_FUNCTION_SIZE sizeof(struct ctf_function)

#endif

