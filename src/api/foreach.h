#ifndef CTF_API_FOREACH_H
#define CTF_API_FOREACH_H

#include "file/errors.h"

/* FUNCTION_NAME(OWNER_TYPE owner, void* data, void (*fn)(LIST_TYPE, void*)) \ */

#define _CTF_FOREACH_PROTO(FUNCTION_NAME, OWNER_TYPE, LIST_TYPE) \
int \
FUNCTION_NAME(OWNER_TYPE owner, void* data, void (*fn)(void*, void*));

#define _CTF_FOREACH_IMPL(FUNCTION_NAME, OWNER_TYPE, LIST_TYPE, LIST_NAME) \
int \
FUNCTION_NAME(OWNER_TYPE owner, void* data, void (*fn)(void*, void*)) \
{ \
	m_list_map(&owner->LIST_NAME, fn, data); \
	return CTF_OK; \
}

#endif

