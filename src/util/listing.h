#ifndef CTF_LISTING_H
#define CTF_LISTING_H

#include "file/errors.h"

#include <stdlib.h>

/*
 * General concept of traversing list-like data structures in libctf. By 
 * introducing this macro we ensure a standard behaviour of all listing
 * functions and in case of any change, it must be made only in this one 
 * place. 
 * 
 * Prototype:
 * get_next (list-like structure, element current, element* next)
 * 
 * Usage:
 * In order to obtain the first element of the structure, second argument,
 * current, needs to be NULL. Any other successor is obtained by supplying
 * its precursor as the second argument. In both previous cases, if all 
 * arguments are non-NULL, the return value is CTF_OK.  
 * In case that the current element supplied is the last one, CTF_END is
 * returned.  
 * If the current element is NULL and the structure is empty,
 * CTF_EMPTY is returned.  
 * If the structure or the output pointer are NULL, CTF_E_NULL is returned.
 */


#define _CTF_LISTING_PROTO(FUNCTION_NAME, OBJECT_TYPE, ELEMENT_TYPE) \
int \
FUNCTION_NAME (OBJECT_TYPE object, ELEMENT_TYPE current, ELEMENT_TYPE* \
out_next);

#define _CTF_LISTING_IMPL(FUNCTION_NAME, OBJECT_TYPE, ELEMENT_TYPE, HEAD_NAME, \
    NEXT_NAME) \
int \
FUNCTION_NAME (OBJECT_TYPE object, ELEMENT_TYPE current, ELEMENT_TYPE* \
out_next) \
{                                                          \
	if (object && out_next)                                  \
	{                                                        \
		if (current)                                           \
		{                                                      \
			ELEMENT_TYPE next = TAILQ_NEXT(current, NEXT_NAME); \
			if (next)                                            \
			{                                                    \
				*out_next = next;                                  \
				return CTF_OK;                                     \
			}                                                    \
			else                                                 \
				return CTF_END;                                    \
		}                                                      \
		else                                                   \
		{                                                      \
			if (TAILQ_EMPTY(object->HEAD_NAME))                  \
				return CTF_EMPTY;                                  \
			*out_next = TAILQ_FIRST(object->HEAD_NAME);          \
			return CTF_OK;                                       \
		}                                                      \
	}                                                        \
	else                                                     \
		return CTF_E_NULL;                                     \
}
#endif

