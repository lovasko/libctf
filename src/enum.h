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
#define _CTF_ENUM_ENTRY_SIZE sizeof(struct _ctf_enum_entry)

/**
 * Enum entry.
 */
struct ctf_enum_entry
{
	char *name; /**< name of the entry */
	int32_t value; /**< value of the entry */

	LIST_ENTRY(ctf_enum_entry) entries;
};
#define CTF_ENUM_ENTRY_SIZE sizeof(struct ctf_enum_entry)

LIST_HEAD(ctf_enum_head, ctf_enum_entry);
#define CTF_ENUM_HEAD_SIZE sizeof(struct ctf_enum_head)

#endif

