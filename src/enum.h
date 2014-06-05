#ifndef CTF_ENUM_H
#define CTF_ENUM_H

#include <stdint.h>

/**
 * Binary reflection of the enum variant data.
 *
 * Designated for internal use only.
 */
struct _ctf_enum_entry
{
	uint32_t name; /**< name of the enum element */
	int32_t value; /**< value associated with this element */
};
#define _CTF_ENUM sizeof(struct _ctf_enum)

#endif

