#ifndef CTF_SECTION_H
#define CTF_SECTION_H

#include <stdlib.h>

/**
 * Simplified representation of the ELF section.
 */
struct ctf_section
{
	void *data; /**< section data */
	size_t size; /**< section size in bytes */
};
#define CTF_SECTION_SIZE sizeof(struct ctf_section)

#endif

