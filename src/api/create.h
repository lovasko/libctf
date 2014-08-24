#ifndef CTF_CREATE_H
#define CTF_CREATE_H

#include <stdlib.h>

/* TODO kernel space malloc and memset */

#define _CTF_CREATE_PROTO(FUNCTION_NAME, TYPE) \
TYPE \
FUNCTION_NAME ();

#define _CTF_CREATE_IMPL(FUNCTION_NAME, TYPE, SIZE) \
TYPE \
FUNCTION_NAME () \
{ \
	void* result = malloc(SIZE); \
	memset(result, 0, SIZE); \
	return result; \
}

#endif

