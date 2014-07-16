#ifndef CTF_BOOL_H
#define CTF_BOOL_H

#include <stdint.h>

/*
 * Since there is no standardized and usable concept of true/false type in
 * C, we introduced our own type. Normally, boolean type in stdbool.h needs
 * a whole int type to represent the value, which is a waste. Instead, we 
 * take up only one byte of memory.
 */

#define CTF_FALSE 0
#define CTF_TRUE  1

typedef uint8_t ctf_bool;

#endif

