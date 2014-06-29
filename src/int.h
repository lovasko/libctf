#ifndef CTF_INT_H
#define CTF_INT_H

#include "util/property.h"

#include <stdint.h>

#define CTF_INT_CONTENT_NUMBER  1
#define CTF_INT_CONTENT_CHAR    2
#define CTF_INT_CONTENT_BOOLEAN 3
#define CTF_INT_CONTENT_VARARGS 4

struct ctf_int
{
	char *name;
	uint8_t content;
	uint8_t offset;
	uint16_t size;
	int is_signed;
};
#define CTF_INT_SIZE sizeof(struct ctf_int)

_CTF_GET_PROPERTY_PROTO(ctf_int_get_name, struct ctf_int*, char*, name)
_CTF_GET_PROPERTY_PROTO(ctf_int_get_size, struct ctf_int*, uint16_t, size)
_CTF_GET_PROPERTY_PROTO(ctf_int_get_offset, struct ctf_int*, uint8_t, offset)
_CTF_GET_PROPERTY_PROTO(ctf_int_get_content, struct ctf_int*, uint8_t, content)
_CTF_GET_PROPERTY_PROTO(ctf_int_is_signed, struct ctf_int*, int, is_signed)

#endif

