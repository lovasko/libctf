#ifndef CTF_COUNT_H
#define CTF_COUNT_H

#include <sys/stdint.h>

/* Type used everywhere where count (number of) some items is relevant. */
typedef uint64_t ctf_count;
#define CTF_COUNT_MIN          0
#define CTF_COUNT_MAX 0xffffffff

#endif

