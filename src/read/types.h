#ifndef CTF_READ_TYPES_H
#define CTF_READ_TYPES_H

#include "strings.h"
#include "../file.h"
#include "../util/section.h"

/**
 * Parse data section containing CTF types.
 *
 * All type data is stored as generic type header (either small or large),
 * and some kinds of types (like enums, functions or floats) contain
 * consecutive variable data section, describing needed details of the 
 * type in question. More on the exact algorithm in the types.c and on the
 * variable data in vardata.h/.c.
 *
 * @param file CTF data
 * @param section section holding the type information
 * @param strings tables to help name resolving
 * @return CTF_OK on success, one of CTF_E_* otherwise
 */
int
_ctf_read_types (struct ctf_file* file, struct _section* section, 
    struct _strings* strings);

#endif

