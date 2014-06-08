#ifndef CTF_STRINGS_H
#define CTF_STRINGS_H

#include "util/section.h"

#include <stdint.h>

struct _strings
{
	struct _section *ctf;
	struct _section *elf;
};

char*
strings_lookup (struct _strings *strings, uint32_t reference);

#endif

