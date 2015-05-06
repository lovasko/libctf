#ifndef CTF_API_FOREACH_H
#define CTF_API_FOREACH_H

#include "file/errors.h"

#define _CTF_FOREACH_PROTO(FUNCTION_NAME, OWNER_TYPE, LIST_TYPE) \
int \
FUNCTION_NAME(OWNER_TYPE owner, void* data, void (*fn)(LIST_TYPE, void*));

#define _CTF_FOREACH_IMPL(FUNCTION_NAME, OWNER_TYPE, LIST_TYPE, NEXT_FN_NAME) \
int \
FUNCTION_NAME(OWNER_TYPE owner, void* data, void (*fn)(LIST_TYPE, void*)) \
{ \
	LIST_TYPE runner; \
	int retval; \
	runner = NULL; \
	while ((retval = NEXT_FN_NAME(owner, runner, &runner)) == CTF_OK) \
		fn(runner, data);	\
	return retval; \
}

#endif

