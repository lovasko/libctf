#ifndef CTF_INT_FLOAT_H
#define CTF_INT_FLOAT_H

#define CTF_INT_FLOAT_ENCODING_MASK 0xff000000
#define CTF_INT_FLOAT_OFFSET_MASK   0x00ff0000 
#define CTF_INT_FLOAT_SIZE_MASK     0x0000ffff 

/**
 * Common variable data for int and float kinds.
 */
struct ctf_int_float_vardata
{
	uint8_t encoding;
	uint8_t offset;
	uint16_t size;
};
#define CTF_INT_FLOAT_VARDATA_SIZE sizeof(struct ctf_int_float_vardata)

#define CTF_INT_SIGNED  1
#define CTF_INT_CHAR    2
#define CTF_INT_BOOL    4
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

#endif

