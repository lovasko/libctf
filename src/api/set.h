#ifndef CTF_PROPERTY_SET_H
#define CTF_PROPERTY_SET_H

#include "../errors.h"

#include <stdlib.h>

#define _CTF_PROPERTY_SET_PROTO(FUNCTION_NAME, OBJECT_TYPE, PROPERTY_TYPE) \
int \
FUNCTION_NAME (OBJECT_TYPE object, PROPERTY_TYPE new_value);

#define _CTF_PROPERTY_SET_IMPL(FUNCTION_NAME, OBJECT_TYPE, PROPERTY_TYPE, \
    PROPERTY_NAME) \
int \
FUNCTION_NAME (OBJECT_TYPE object, PROPERTY_TYPE new_value) \
{ \
	if (object == NULL) \
		return CTF_E_NULL; \
\
	object->PROPERTY_NAME = new_value; \
	return CTF_OK; \
}

#endif

