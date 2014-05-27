#ifndef CTF_FILE_H
#define CTF_FILE_H

#include "label.h"

/**
 * Root CTF data strcture.
 *
 * Does not represent the exact binary reflection of the saved data. Instead,
 * it is suited for consuming the data by applications.
 */
struct ctf_file
{
	int compressed; /**< 0/1 false/true flag for the compression */
	int version; /**< version indicator */
	struct ctf_label *labels; /**< linked list containing labels */
};

#endif

