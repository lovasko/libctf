#include "errors.h"

#define _CTF_GET_PROPERTY_PROTO(FUNCTION_NAME, OBJECT_TYPE, PROPERTY_TYPE, \
    PROPERTY_NAME) \
int \
FUNCTION_NAME (OBJECT_TYPE object, PROPERTY_TYPE* out_property);

#define _CTF_GET_PROPERTY_IMPL(FUNCTION_NAME, OBJECT_TYPE, PROPERTY_TYPE, \
    PROPERTY_NAME) \
int \
FUNCTION_NAME (OBJECT_TYPE object, PROPERTY_TYPE* out_property) \
{                                          \
	if (object && out_property)              \
	{                                        \
		*out_property = object->PROPERTY_NAME; \
		return CTF_OK;                         \
	}                                        \
	else                                     \
		return CTF_E_NULL;                     \
}

