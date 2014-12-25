#ifndef CTF_ADD_H
#define CTF_ADD_H

#include <sys/queue.h>
#include <sys/stddef.h>

#include "file/errors.h"

#define _CTF_ADD_PROTO(FUNCTION_NAME, OBJECT_TYPE, VALUE_TYPE) \
int \
FUNCTION_NAME (OBJECT_TYPE object, VALUE_TYPE value);

#define _CTF_ADD_IMPL(FUNCTION_NAME, OBJECT_TYPE, VALUE_TYPE, LIST_NAME, \
  LIST_ENTRY_NAME, LIST_COUNTER) \
int \
FUNCTION_NAME (OBJECT_TYPE object, VALUE_TYPE value) \
{ \
	if (object != NULL) \
	{ \
		if (object->LIST_NAME != NULL) \
		{ \
			TAILQ_INSERT_TAIL(object->LIST_NAME, value, LIST_ENTRY_NAME); \
			object->LIST_COUNTER++; \
			return CTF_OK; \
		} \
		else \
			return CTF_E_NULL; \
	} \
	else \
		return CTF_E_NULL; \
}

#endif

