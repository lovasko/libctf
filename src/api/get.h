#ifndef CTF_GET_H
#define CTF_GET_H

#include "file/errors.h"

/* 
 * Property getter generator macro.  
 * 
 * In case of successful retrieval, CTF_OK is returned.
 * If either the object or the out-pointer are NULL, CTF_E_NULL is returned.
 */

#define _CTF_GET_PROPERTY_PROTO(FUNCTION_NAME, OBJECT_TYPE, PROPERTY_TYPE) \
int \
FUNCTION_NAME (OBJECT_TYPE object, PROPERTY_TYPE* out_property);

#define _CTF_GET_PROPERTY_IMPL(FUNCTION_NAME, OBJECT_TYPE, PROPERTY_TYPE, \
    PROPERTY_NAME) \
int \
FUNCTION_NAME (OBJECT_TYPE object, PROPERTY_TYPE* out_property) \
{ \
	if (object && out_property) \
	{ \
		*out_property = object->PROPERTY_NAME; \
		return CTF_OK; \
	} \
	else \
		return CTF_E_NULL; \
}

#endif

