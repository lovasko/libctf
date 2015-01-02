#ifndef CTF_CREATE_H
#define CTF_CREATE_H

#include "file/errors.h"

#include <stdlib.h>
#include <string.h>

/* TODO create smaller __CTF_ALLOCATE and __CTF_SETUP_LIST macros */
#define __CTF_CREATE_ALLOCATE(OBJECT_SIZE) \
	void* object = malloc(OBJECT_SIZE); \
	memset(object, 0, OBJECT_SIZE); \

#define __CTF_CREATE_SETUP_LIST(OBJECT_TYPE, LIST_NAME, LIST_HEAD_SIZE, \
    LIST_COUNTER_NAME) \
	((OBJECT_TYPE)object)->LIST_NAME = malloc(LIST_HEAD_SIZE); \
	TAILQ_INIT(((OBJECT_TYPE)object)->LIST_NAME); \
	((OBJECT_TYPE)object)->LIST_COUNTER_NAME = 0; \


#define _CTF_CREATE_PROTO(FUNCTION_NAME, OBJECT_TYPE) \
OBJECT_TYPE \
FUNCTION_NAME ();

#define _CTF_CREATE_IMPL(FUNCTION_NAME, OBJECT_TYPE, OBJECT_SIZE) \
OBJECT_TYPE \
FUNCTION_NAME () \
{ \
	void* object = malloc(OBJECT_SIZE); \
	memset(object, 0, OBJECT_SIZE); \
	return object; \
}

#define _CTF_CREATE_1_LIST_IMPL(FUNCTION_NAME, OBJECT_TYPE, OBJECT_SIZE, \
  LIST_NAME, LIST_HEAD_SIZE, LIST_COUNTER_NAME) \
OBJECT_TYPE \
FUNCTION_NAME () \
{ \
	void* object = malloc(OBJECT_SIZE); \
	memset(object, 0, OBJECT_SIZE); \
	((OBJECT_TYPE)object)->LIST_NAME = malloc(LIST_HEAD_SIZE); \
	TAILQ_INIT(((OBJECT_TYPE)object)->LIST_NAME); \
	((OBJECT_TYPE)object)->LIST_COUNTER_NAME = 0; \
	return object; \
}

#define _CTF_CREATE_4_LIST_IMPL(FUNCTION_NAME, OBJECT_TYPE, OBJECT_SIZE, \
  LIST1_NAME, LIST1_COUNTER_NAME, \
	LIST2_NAME, LIST2_COUNTER_NAME, \
	LIST3_NAME, LIST3_COUNTER_NAME, \
	LIST4_NAME, LIST4_COUNTER_NAME) \
OBJECT_TYPE \
FUNCTION_NAME () \
{ \
	void* object = malloc(OBJECT_SIZE); \
	memset(object, 0, OBJECT_SIZE); \
	TAILQ_INIT(((OBJECT_TYPE)object)->LIST1_NAME); \
	((OBJECT_TYPE)object)->LIST1_COUNTER_NAME = 0; \
	TAILQ_INIT(((OBJECT_TYPE)object)->LIST2_NAME); \
	((OBJECT_TYPE)object)->LIST2_COUNTER_NAME = 0; \
	TAILQ_INIT(((OBJECT_TYPE)object)->LIST3_NAME); \
	((OBJECT_TYPE)object)->LIST3_COUNTER_NAME = 0; \
	TAILQ_INIT(((OBJECT_TYPE)object)->LIST4_NAME); \
	((OBJECT_TYPE)object)->LIST4_COUNTER_NAME = 0; \
	return object; \
}

#endif

