#ifndef CTF_FUNCTION_H
#define CTF_FUNCTION_H

#include "type.h"
#include "argument.h"

struct ctf_function
{
	struct ctf_type *return_type;
	struct ctf_argument_head *argument_head;
};
#define CTF_FUNCTION_SIZE sizeof(struct ctf_function)

#endif

