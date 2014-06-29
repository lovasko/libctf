#include "errors.h"

#include <stdlib.h>

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

