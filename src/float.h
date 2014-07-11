#ifndef CTF_FLOAT_H
#define CTF_FLOAT_H

#include "util/property.h"

#include <stdint.h>

#define CTF_FLOAT_ENCODING_MIN                    1
#define CTF_FLOAT_ENCODING_SINGLE                 1
#define CTF_FLOAT_ENCODING_DOUBLE                 2
#define CTF_FLOAT_ENCODING_COMPLEX                3
#define CTF_FLOAT_ENCODING_DOUBLE_COMPLEX         4
#define CTF_FLOAT_ENCODING_LONG_DOUBLE_COMPLEX    5
#define CTF_FLOAT_ENCODING_LONG_DOUBLE            6
#define CTF_FLOAT_ENCODING_INTERVAL               7
#define CTF_FLOAT_ENCODING_DOUBLE_INTERVAL        8
#define CTF_FLOAT_ENCODING_LONG_DOUBLE_INTERVAL   9
#define CTF_FLOAT_ENCODING_IMAGINARY             10
#define CTF_FLOAT_ENCODING_DOUBLE_IMAGINARY      11
#define CTF_FLOAT_ENCODING_LONG_DOUBLE_IMAGINARY 12
#define CTF_FLOAT_ENCODING_MAX                   12

typedef uint8_t ctf_float_encoding

struct ctf_float
{
	char* name;
	ctf_float_encoding encoding;
	uint8_t offset;
	uint16_t size;
};
#define CTF_FLOAT_SIZE sizeof(struct ctf_float)

_CTF_GET_PROPERTY_PROTO(ctf_float_get_name, struct ctf_float*, char*)
_CTF_GET_PROPERTY_PROTO(ctf_float_get_size, struct ctf_float*, uint16_t)
typedef struct ctf_float* ctf_float;

_CTF_GET_PROPERTY_PROTO(ctf_float_get_offset, struct ctf_float*, uint8_t)
_CTF_GET_PROPERTY_PROTO(ctf_float_get_encoding, struct ctf_float*, uint8_t) 

#endif

