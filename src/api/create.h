#ifndef CTF_CREATE_H
#define CTF_CREATE_H

#include "file/errors.h"

#include <stdlib.h>
#include <string.h>

#define __CTF_CREATE_ALLOCATE(OBJECT_TYPE, OBJECT_SIZE) \
	OBJECT_TYPE object = malloc(OBJECT_SIZE); \
	memset(object, 0, OBJECT_SIZE); \

#define __CTF_CREATE_SETUP_LIST(LIST_NAME) \
	m_list_init(&object->LIST_NAME);

#define _CTF_CREATE_PROTO(FUNCTION_NAME, OBJECT_TYPE) \
OBJECT_TYPE \
FUNCTION_NAME ();

#define _CTF_CREATE_IMPL(FUNCTION_NAME, OBJECT_TYPE, OBJECT_SIZE) \
OBJECT_TYPE \
FUNCTION_NAME () \
{ \
	__CTF_CREATE_ALLOCATE(OBJECT_TYPE, OBJECT_SIZE) \
	return object; \
}

#define _CTF_CREATE_1_LIST_IMPL(FUNCTION_NAME, OBJECT_TYPE, OBJECT_SIZE, LIST_NAME) \
OBJECT_TYPE \
FUNCTION_NAME () \
{ \
	__CTF_CREATE_ALLOCATE(OBJECT_TYPE, OBJECT_SIZE) \
	__CTF_CREATE_SETUP_LIST(LIST_NAME) \
	return object; \
}

#define _CTF_CREATE_4_LIST_IMPL(FUNCTION_NAME, OBJECT_TYPE, OBJECT_SIZE, \
                                LIST1_NAME, LIST2_NAME, LIST3_NAME, LIST4_NAME) \
OBJECT_TYPE \
FUNCTION_NAME () \
{ \
	__CTF_CREATE_ALLOCATE(OBJECT_TYPE, OBJECT_SIZE) \
	__CTF_CREATE_SETUP_LIST(LIST1_NAME) \
	__CTF_CREATE_SETUP_LIST(LIST2_NAME) \
	__CTF_CREATE_SETUP_LIST(LIST3_NAME) \
	__CTF_CREATE_SETUP_LIST(LIST4_NAME) \
	return object; \
}

#endif

