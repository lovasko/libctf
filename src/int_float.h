#ifndef CTF_INT_FLOAT_H
#define CTF_INT_FLOAT_H

#include <stdint.h>

#define CTF_INT_FLOAT_ENCODING_MASK 0xff000000
#define CTF_INT_FLOAT_OFFSET_MASK   0x00ff0000 
#define CTF_INT_FLOAT_SIZE_MASK     0x0000ffff 

#define CTF_INT_SIGNED  1
#define CTF_INT_CHAR    2
#define CTF_INT_BOOLEAN 4
#define CTF_INT_VARARGS 8

#define CTF_FLOAT_SINGLE                 1
#define CTF_FLOAT_DOUBLE                 2
#define CTF_FLOAT_COMPLEX                3
#define CTF_FLOAT_DOUBLE_COMPLEX         4
#define CTF_FLOAT_LONG_DOUBLE_COMPLEX    5
#define CTF_FLOAT_LONG_DOUBLE            6
#define CTF_FLOAT_INTERVAL               7
#define CTF_FLOAT_DOUBLE_INTERVAL        8
#define CTF_FLOAT_LONG_DOUBLE_INTERVAL   9
#define CTF_FLOAT_IMAGINARY             10
#define CTF_FLOAT_DOUBLE_IMAGINARY      11
#define CTF_FLOAT_LONG_DOUBLE_IMAGINARY 12
#define CTF_FLOAT_MAX                   12

/**
 * Common variable data for int and float kinds.
 */
struct ctf_int_float
{
	uint8_t encoding;
	uint8_t offset;
	uint16_t size;
};
#define CTF_INT_FLOAT_SIZE sizeof(struct ctf_int_float)

int
ctf_int_float_get_size (struct ctf_int_float *int_float, uint16_t *out_size);

int
ctf_int_float_get_offset (struct ctf_int_float *int_float, uint8_t *out_offset);

int
ctf_int_is_signed (struct ctf_int_float *int_float, int *out_is_signed);

int
ctf_int_is_char (struct ctf_int_float *int_float, int *out_is_char);

int
ctf_int_is_boolean (struct ctf_int_float *int_float, int *out_is_boolean);

int
ctf_int_is_varargs (struct ctf_int_float *int_float, int *out_is_varargs);

int
ctf_float_get_encoding (struct ctf_int_float *int_float, int *out_encoding);

#endif

