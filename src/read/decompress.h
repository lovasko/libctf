#ifndef CTF_COMPRESSION_H
#define CTF_COMPRESSION_H

#include "util/section.h"

/**
 * Perform a ZIP decompression on a data section.
 *
 * @param to_decompress data section to decompress
 * @return decompressed data
 */
struct _section*
decompress (struct _section* to_decompress);

#endif

