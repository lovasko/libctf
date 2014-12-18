#ifndef CTF_INT_H
#define CTF_INT_H

#include "api/from_type.h"
#include "api/property.h"
#include "api/create.h"

#include <stdint.h>

typedef uint8_t ctf_int_content;
#define CTF_INT_CONTENT_NUMBER  1
#define CTF_INT_CONTENT_CHAR    2
#define CTF_INT_CONTENT_BOOLEAN 3
#define CTF_INT_CONTENT_VARARGS 4

typedef uint8_t ctf_int_offset;
#define CTF_INT_OFFSET_MIN   0
#define CTF_INT_OFFSET_MAX 255

typedef uint16_t ctf_int_size;
#define CTF_INT_SIZE_MIN     0
#define CTF_INT_SIZE_MAX 65535

/**
 * Int.
 */
struct ctf_int
{
	char* name;
	ctf_int_content content;
	ctf_int_offset offset;
	ctf_int_size size;
	uint8_t is_signed;
};
#define CTF_INT_SIZE sizeof(struct ctf_int)

typedef struct ctf_int* ctf_int;

_CTF_GET_PROPERTY_PROTO(ctf_int_get_name, ctf_int, char*)
_CTF_SET_PROPERTY_PROTO(ctf_int_set_name, ctf_int, char*)

_CTF_GET_PROPERTY_PROTO(ctf_int_get_size, ctf_int, ctf_int_size)
_CTF_SET_PROPERTY_PROTO(ctf_int_set_size, ctf_int, ctf_int_size)

_CTF_GET_PROPERTY_PROTO(ctf_int_get_offset, ctf_int, ctf_int_offset)
_CTF_SET_PROPERTY_PROTO(ctf_int_set_offset, ctf_int, ctf_int_offset)

_CTF_GET_PROPERTY_PROTO(ctf_int_get_content, ctf_int, ctf_int_content)
_CTF_SET_PROPERTY_PROTO(ctf_int_set_content, ctf_int, ctf_int_content)

_CTF_GET_PROPERTY_PROTO(ctf_int_get_is_signed, ctf_int, uint8_t)
_CTF_SET_PROPERTY_PROTO(ctf_int_set_is_signed, ctf_int, uint8_t)

_CTF_FROM_TYPE_PROTO(ctf_int_init, ctf_int)
_CTF_CREATE_PROTO(ctf_int_create, ctf_int)

const char*
ctf_int_content_to_string(ctf_int_content int_content);

#endif

