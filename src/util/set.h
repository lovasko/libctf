#ifndef CTF_SET_H
#define CTF_SET_H

#include "file/errors.h"

/* 
 * Property setter generator macro.  
 * 
 * In case of successful setting the new value, CTF_OK is returned.
 * If either the object is NULL, CTF_E_NULL is returned.
 */

#define _CTF_SET_PROPERTY_PROTO(FUNCTION_NAME, OBJECT_TYPE, PROPERTY_TYPE) \
int \
FUNCTION_NAME (OBJECT_TYPE object, PROPERTY_TYPE property);

#define _CTF_SET_PROPERTY_IMPL(FUNCTION_NAME, OBJECT_TYPE, PROPERTY_TYPE, \
    PROPERTY_NAME) \
int \
FUNCTION_NAME (OBJECT_TYPE object, PROPERTY_TYPE value) \
{ \
	if (object) \
	{ \
		object->PROPERTY_NAME = value; \
		return CTF_OK; \
	} \
	else \
		return CTF_E_NULL; \
}

#endif

