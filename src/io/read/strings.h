#ifndef CTF_READ_STRINGS_H
#define CTF_READ_STRINGS_H

#include "util/section.h"

#include <stdint.h>

/**
 * Tuple holding pointers to two string tables: ELF and CTF.
 */
struct _strings
{
	struct _section* ctf;
	struct _section* elf;
};

/**
 * Look up a string identified by the reference from either ELF or CTF string
 * table.
 *
 * @param strings tuple of string tables
 * @param reference string reference
 * @return pointer to NULL-terminated const string 
 */
const char*
_ctf_strings_lookup (struct _strings* strings, uint32_t reference);

#endif

