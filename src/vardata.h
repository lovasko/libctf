#ifndef CTF_VARDATA_H
#define CTF_VARDATA_H

#include "type.h"

#include <stdint.h>

#define CTF_VARDATA_LENGTH_MAX 0x3ff

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

void*
read_int_float_vardata (void *data);

void*
read_array_vardata (void *data, struct ctf_type **id_table);

void*
read_function_vardata (void *data, struct ctf_type **id_table, uint16_t length,
    struct ctf_type *return_type);

void*
read_enum_vardata (void *data, uint16_t length);

void*
read_struct_union_vardata (void *data, struct ctf_type **id_table, 
    uint16_t length, uint16_t size);

#endif

