#ifndef CTF_COMPRESSION_H
#define CTF_COMPRESSION_H

#include "section.h"

#include <zlib.h>
#include <stdlib.h>

struct ctf_section*
decompress (struct ctf_section *to_decompress);

#endif

