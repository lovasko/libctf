#ifndef CTF_API_COUNT_H
#define CTF_API_COUNT_H

#include <sys/stddef.h>

#include <m_list.h>

#include "file/errors.h"
#include "util/count.h"

#define _CTF_COUNT_PROTO(FUNCTION_NAME, OBJECT_TYPE) \
int \
FUNCTION_NAME(OBJECT_TYPE object, ctf_count* out_count);

#define _CTF_COUNT_IMPL(FUNCTION_NAME, OBJECT_TYPE, LIST_NAME) \
int \
FUNCTION_NAME(OBJECT_TYPE object, ctf_count* out_count) \
{ \
	uint64_t size; \
	if (object == NULL || out_count == NULL) \
		return CTF_E_NULL; \
	m_list_size(&object->LIST_NAME, &size); \
	*out_count = size; \
	return CTF_OK; \
}

#endif

