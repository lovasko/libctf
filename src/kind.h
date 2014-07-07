#ifndef CTF_KIND_H
#define CTF_KIND_H

#include <stdint.h>

/* KIND constants that are contained in the type information */

#define CTF_KIND_MIN       0

#define CTF_KIND_NONE      0
#define CTF_KIND_INT       1
#define CTF_KIND_FLOAT     2
#define CTF_KIND_POINTER   3
#define CTF_KIND_ARRAY     4
#define CTF_KIND_FUNC      5
#define CTF_KIND_STRUCT    6
#define CTF_KIND_UNION     7
#define CTF_KIND_ENUM      8
#define CTF_KIND_FWD_DECL  9
#define CTF_KIND_TYPEDEF  10
#define CTF_KIND_VOLATILE 11
#define CTF_KIND_CONST    12
#define CTF_KIND_RESTRICT 13

/* current maximum of KIND constants (all others should be <=) */
#define CTF_KIND_MAX      13

/**
 * Extract the kind from a type information.
 *
 * @param info the type information
 * @return one of the CTF_KIND constants 
 */
uint8_t
ctf_kind_from_info (uint16_t info);

/**
 * Test whether the kind is one of the reference kinds.
 *
 * Reference kinds are: pointer, typedef, const, volatile and restrict.
 * Their common property is, that they do not represent a standalone type, but
 * just a marker property for some other type. 
 *
 * @param kind the type kind 
 * @return 1 if the kind is a reference, 0 otherwise.
 */
int
ctf_kind_is_pure_reference (uint8_t kind);

/**
 * Test whether the kind is one of the special kinds.
 * 
 * Special kinds are: none and forward.
 * There is no extra parsing of these kinds: none is used only for padding
 * purposes and forward denotes a forward declaration of some other type.
 * 
 * @param kind the type kind
 * @return 1 if the kind is special, 0 otherwise.
 */
int
ctf_kind_is_special (uint8_t kind);

/**
 * Test whether the kind is one of the complex kinds.
 *
 * Complex kinds are: int, float, array, function, enum, struct and union.
 * All of the special kinds require parsing of the variable data and none of
 * them reference any other type (only inside the variable data).
 *
 * @param kind the type kind
 * @return 1 if the kind is complex, 0 otherwise.
 */
int
ctf_kind_is_complex (uint8_t kind);

#endif

