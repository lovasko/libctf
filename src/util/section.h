#ifndef CTF_SECTION_H
#define CTF_SECTION_H

#include <stdlib.h>

/**
 * Simplified representation of the ELF section.
 */
struct _section
{
	void *data; /**< section data */
	size_t size; /**< section size in bytes */
};
#define _SECTION_SIZE sizeof(struct _section)

#endif

