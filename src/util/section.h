#ifndef CTF_SECTION_H
#define CTF_SECTION_H

#include <stdlib.h>

/**
 * Simplified representation of universal data section.
 * Data sections can be a ELF sections, CTF subsections or any general block of
 * binary data.
 * Designated for internal use only.
 */
struct _section
{
	void *data; /**< section data */
	size_t size; /**< section size in bytes */
};
#define _SECTION_SIZE sizeof(struct _section)

#endif

