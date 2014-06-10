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

/**
 * Read the inf/float variable data.
 *
 * The variable data for both kinds is long exactly 4 bytes. Each one of these
 * bytes is described in the ctf_int_float_vardata struct.
 *
 * @param data start of the variable data
 * @return pointer to filled ctf_int_float_vardata struct
 */
void*
read_int_float_vardata (void *data);

/**
 * Read the array variable data.
 * 
 * The array variable data is the binary reflection of the _ctf_array struct.
 * It is exactly _CTF_ARRAY_SIZE bytes long.
 * 
 * @param data start of the variable data
 * @param id_table ID to ctf_type table used to solve the array content type
 * @return pointer to filled ctf_array struct
 */
void*
read_array_vardata (void *data);

/**
 * Read the function variable data.
 *
 * The function variable data is just a list of uint16_t which are references
 * to the id_table. Length of the list is the length parameter. The return type
 * parameter is here only because we want to complete the ctf_function struct.
 * 
 * The actual length of the variable data is always an even number, even if the
 * argument count is odd. This is adjusted in the read function.
 * 
 * @param data start of the variable data
 * @param id_table ID to ctf_type table used to solve the argument types
 * @param length number of the arguments (can be odd)
 * @param return_type return type of the function - this is resolved in the
 * read function already
 * @return pointer to filled ctf_function struct
 */
void*
read_function_vardata (void *data, uint16_t length);

/**
 * Read the enum variable data.
 *
 * The enum variable data is a length-long list of binary reflections of the
 * _ctf_enum_entry structs.
 *
 * @param data start of the variable data
 * @param length number of enum entries
 * @return pointer to filled ctf_enum_head struct
 */
void*
read_enum_vardata (void *data, uint16_t length, struct _strings *strings);

/**
 * Read the struct/union variable data.
 *
 * Both, the struct and the union, have identical variable data. Based on the
 * value of the size parameter (threshold is the CTF_MEMBER_THRESHOLD), the
 * variable list composed of either small_member entries or large_member
 * entires.
 *
 * @param data start of the variable data
 * @param id_table ID to ctf_type table used to solve the member types
 * @param length number of the member entries (oblivious to the member size)
 * @param size size of the vardata in bytes
 * @return pointer to filled ctf_member_head struct
 */
void*
read_struct_union_vardata (void *data, uint16_t length, uint16_t size, 
    struct _strings *strings);

#endif

