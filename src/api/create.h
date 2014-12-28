#ifndef CTF_CREATE_H
#define CTF_CREATE_H

#include "file/errors.h"

#include <stdlib.h>
#include <string.h>

#define _CTF_CREATE_PROTO(FUNCTION_NAME, OBJECT_TYPE) \
OBJECT_TYPE \
FUNCTION_NAME ();

#define _CTF_CREATE_IMPL(FUNCTION_NAME, OBJECT_TYPE, OBJECT_SIZE) \
OBJECT_TYPE \
FUNCTION_NAME () \
{ \
	void* object = malloc(OBJECT_SIZE); \
	bzero(object, OBJECT_SIZE); \
	return object; \
}

#define _CTF_CREATE_1_LIST_IMPL(FUNCTION_NAME, OBJECT_TYPE, OBJECT_SIZE, \
  LIST_NAME, LIST_COUNTER_NAME) \
OBJECT_TYPE \
FUNCTION_NAME () \
{ \
	void* object = malloc(OBJECT_SIZE); \
	bzero(object, OBJECT_SIZE); \
	TAILQ_INIT(((OBJECT_TYPE)object)->LIST_NAME); \
	((OBJECT_TYPE)object)->LIST_COUNTER_NAME = 0; \
	return object; \
}

#endif

