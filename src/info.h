#ifndef CTF_INFO_H
#define CTF_INFO_H

#include <stdint.h>

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

