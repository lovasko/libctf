#ifndef CTF_FUNCTION_H
#define CTF_FUNCTION_H

#include "type/type.h"
#include "object/function/argument.h"
#include "util/from_type.h"
#include "util/property.h"
#include "util/listing.h"

#include <stdint.h>
#include <sys/queue.h>

/**
 * Function vardata.
 */
struct ctf_function
{
	char* name;
	union
	{
		ctf_type return_type; /**< return type of the function */
		ctf_id return_id;
	};
	struct ctf_argument_head* argument_head; /**< linked list of arguments */

	TAILQ_ENTRY(ctf_function) functions;
};
#define CTF_FUNCTION_SIZE sizeof(struct ctf_function)

typedef struct ctf_function* ctf_function;

TAILQ_HEAD(ctf_function_head, ctf_function);
#define CTF_FUNCTION_HEAD_SIZE sizeof(struct ctf_function_head)

_CTF_GET_PROPERTY_PROTO(ctf_function_get_name, ctf_function, char*)
_CTF_GET_PROPERTY_PROTO(ctf_function_get_return_type, ctf_function, ctf_type)
	
_CTF_LISTING_PROTO(ctf_function_get_next_argument, ctf_function, ctf_argument)

_CTF_FROM_TYPE_PROTO(ctf_function_init, ctf_function)

#endif

