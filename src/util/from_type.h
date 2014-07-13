#ifndef CTF_FROM_TYPE_H
#define CTF_FROM_TYPE_H

#include "../errors.h"
#include "../type.h"

#define _CTF_FROM_TYPE_PROTO(FUNCTION_NAME, SPECIFIC_TYPE) \
int \
FUNCTION_NAME (ctf_type type, SPECIFIC_TYPE* out);

#define _CTF_FROM_TYPE_IMPL(FUNCTION_NAME, SPECIFIC_TYPE) \
int \
FUNCTION_NAME (ctf_type type, SPECIFIC_TYPE* out) \
{ \
	if (type && out) \
	{ \
		*out = type->data; \
		return CTF_OK; \
	} \
	else \
		return CTF_E_NULL; \
}

#endif

