#ifndef CTF_READ_DECOMPRESS_H
#define CTF_READ_DECOMPRESS_H

#ifndef _KERNEL

#include "util/section.h"

/**
 * Perform a ZIP decompression on a data section.
 *
 * @param to_decompress data section to decompress
 * @return decompressed data
 */
struct _section*
_ctf_decompress (struct _section* to_decompress);

#endif /* _KERNEL */

#endif

