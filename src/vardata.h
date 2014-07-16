#ifndef CTF_VARDATA_H
#define CTF_VARDATA_H

#include "array.h"
#include "type.h"
#include "enum.h"
#include "enum_entry.h"
#include "function.h"
#include "argument.h"
#include "member.h"
#include "int.h"
#include "float.h"
#include "strings.h"

#include <stdint.h>

/**
 * Read int variable data.
 *
 * Int variable data is stored as 4 bytes:
 *  - 1. byte = content (see CTF_INT_CONTENT_*)
 *  - 2. byte = offset in bits
 *  - 3. and 4. byte = size in bits
 *
 * @param data pointer to start of the variable data
 * @return parsed ctf_int
 */
struct ctf_int*
read_int_vardata (void* data);

/**
 * Read float variable data.
 *
 * Float variable data is stored as 4 bytes:
 *  - 1. byte = encoding (see CTF_FLOAT_ENCODING_*)
 *  - 2. byte = offset in bits
 *  - 3. and 4. byte = size in bits
 *
 * @param data pointer to start of the variable data
 * @return parsed ctf_float
 */
struct ctf_float*
read_float_vardata (void* data);

/**
 * Read the array variable data.
 * 
 * The array variable data is the binary reflection of the _ctf_array struct.
 * It is exactly _CTF_ARRAY_SIZE bytes long.
 * 
 * @param data start of the variable data
 * @return pointer to filled ctf_array struct
 */
struct ctf_array*
read_array_vardata (void* data);

/**
 * Read the function variable data.
 *
 * The function variable data is a list of uint16_t which are type IDs. 
 * Length of the list is the length parameter. The actual length of 
 * the variable data is always an even number, even if the
 * argument count is odd. This is already adjusted in the calling function.
 * 
 * @param data start of the variable data
 * @param length number of the arguments 
 * @return pointer to filled ctf_function struct
 */
struct ctf_argument_head*
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
struct ctf_enum_head*
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
struct ctf_member_head*
read_struct_union_vardata (void *data, uint16_t length, uint16_t size, 
    struct _strings *strings);

#endif

