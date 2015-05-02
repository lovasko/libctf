#ifndef CTF_INFO_H
#define CTF_INFO_H

#include <sys/stdint.h>

/*
 * Info table.
 *
 * The member info from both, the small_ and large_type, is not a single
 * number, but rather 3 separate variables packed into single 16-bit word.
 * 
 * Bits 0-9 represent the length of the variable data section following the
 * general type information. 
 *
 * Bit 10 represents the boolean flag for the attribute root. 
 *
 * Bits 11-15 form the kind of the types. The kind constants CTF_KIND can be
 * found inside the kind.h file.
 */

/**
 * Extract kind information from info.
 * 
 * @param [in] info info
 * @return kind
 */
uint8_t
_ctf_info_get_kind (uint16_t info);

/**
 * Extract root information from info.
 * 
 * @param [in] info info
 * @return kind
 */
uint8_t
_ctf_info_is_root (uint16_t info);

/**
 * Extract variable data length information from info.
 * 
 * @param [in] info info
 * @return kind
 */
uint16_t
_ctf_info_get_vardata_length (uint16_t info);

#endif

