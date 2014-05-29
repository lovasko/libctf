#ifndef CTF_KIND_H
#define CTF_KIND_H

#include <stdint.h>

/* KIND constants that are contained in the type information */
#define CTF_KIND_NONE 0
#define CTF_KIND_INT 1
#define CTF_KIND_FLOAT 2
#define CTF_KIND_POINTER 3
#define CTF_KIND_ARRAY 4
#define CTF_KIND_FUNC 5
#define CTF_KIND_STRUCT 6
#define CTF_KIND_UNION 7
#define CTF_KIND_ENUM 8
#define CTF_KIND_FORWARD 9
#define CTF_KIND_TYPEDEF 10
#define CTF_KIND_VOLATILE 11
#define CTF_KIND_CONST 12
#define CTF_KIND_RESTRICT 13

/* current maximum of KIND constants (all others should be <=) */
#define CTF_KIND_MAX 13

/**
 * Extract the kind from a type information.
 *
 * @param info the type information
 * @return one of the CTF_KIND constants 
 */
uint8_t
ctf_info_to_kind (uint16_t info);

/**
 * Extract the kind from a type information and create a string representation.
 *
 * @param info the type information
 * @return e.g. "float" for CTF_KIND_FLOAT. If none of the CTF_KINDs were able
 * to match, "unresolvable" is returned.
 */
const char*
ctf_info_to_string (uint16_t info);

int
ctf_kind_is_pure_reference (uint8_t kind);

int
ctf_kind_is_special (uint8_t kind);

#endif

