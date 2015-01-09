#ifndef CTF_MEMORY_USAGE_H
#define CTF_MEMORU_USAGE_H

#include <sys/types.h>

#define _CTF_MEMORY_USAGE_PROTO(FUNCTION_NAME, OBJECT_TYPE) \
size_t \
FUNCTION_NAME (OBJECT_TYPE object);

#endif

