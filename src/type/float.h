#ifndef CTF_FLOAT_H
#define CTF_FLOAT_H

#include <sys/stdint.h>

#include "api/create.h"
#include "api/from_type.h"
#include "api/memory_usage.h"
#include "api/property.h"

typedef uint8_t ctf_float_encoding;
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

typedef uint8_t ctf_float_offset;
#define CTF_FLOAT_OFFSET_MIN   0
#define CTF_FLOAT_OFFSET_MAX 255

typedef uint16_t ctf_float_size;
#define CTF_FLOAT_SIZE_MIN     0
#define CTF_FLOAT_SIZE_MAX 65535

/**
 * Float.
 */
struct ctf_float
{
	char* name;
	ctf_float_encoding encoding;
	ctf_float_offset offset;
	ctf_float_size size;
};
#define CTF_FLOAT_SIZE sizeof(struct ctf_float)

typedef struct ctf_float* ctf_float;

_CTF_GET_PROPERTY_PROTO(ctf_float_get_name, ctf_float, char*)
_CTF_SET_PROPERTY_PROTO(ctf_float_set_name, ctf_float, char*)

_CTF_GET_PROPERTY_PROTO(ctf_float_get_size, ctf_float, ctf_float_size)
_CTF_SET_PROPERTY_PROTO(ctf_float_set_size, ctf_float, ctf_float_size)

_CTF_GET_PROPERTY_PROTO(ctf_float_get_offset, ctf_float, ctf_float_offset)
_CTF_SET_PROPERTY_PROTO(ctf_float_set_offset, ctf_float, ctf_float_offset)

_CTF_GET_PROPERTY_PROTO(ctf_float_get_encoding, ctf_float, ctf_float_encoding)
_CTF_SET_PROPERTY_PROTO(ctf_float_set_encoding, ctf_float, ctf_float_encoding) 

_CTF_MEMORY_USAGE_PROTO(ctf_float_memory_usage, ctf_float)

_CTF_FROM_TYPE_PROTO(ctf_float_init, ctf_float)
_CTF_CREATE_PROTO(ctf_float_create, ctf_float)

const char*
ctf_float_encoding_to_string(ctf_float_encoding float_encoding);

#endif

