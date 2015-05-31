#ifndef CTF_ADD_H
#define CTF_ADD_H

#include <sys/stddef.h>

#include "file/errors.h"

#define _CTF_ADD_PROTO(FUNCTION_NAME, OBJECT_TYPE, VALUE_TYPE) \
int \
FUNCTION_NAME (OBJECT_TYPE object, VALUE_TYPE value);

#define _CTF_ADD_IMPL(FUNCTION_NAME, OBJECT_TYPE, VALUE_TYPE, LIST_NAME) \
int \
FUNCTION_NAME (OBJECT_TYPE object, VALUE_TYPE value) \
{ \
	if (object != NULL) \
	{ \
		m_list_append(&object->LIST_NAME, M_LIST_COPY_SHALLOW, value, 0); \
		return CTF_OK; \
	} \
	else \
		return CTF_E_NULL; \
}

#endif

