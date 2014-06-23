#ifndef CTF_LABEL_H
#define CTF_LABEL_H

#include "util/section.h"
#include "strings.h"
#include "file.h"

#include <stdint.h>
#include <sys/queue.h>

/**
 * Binary reflection of the stored CTF data. 
 *
 * Designated for internal use only.
 */
struct _ctf_label
{
	uint32_t name; /**< reference to the name */
	uint32_t index; /**< starting index in the type table */
};
#define _CTF_LABEL_SIZE sizeof(struct _ctf_label)

/**
 * Parsed and resolved CTF label.
 */
struct ctf_label
{
	char *name; /**< resolved name */
	uint32_t index; /**< starting index in the type table */

	TAILQ_ENTRY(ctf_label) labels; /**< pointer to next labels */
};
#define CTF_LABEL_SIZE sizeof(struct ctf_label)

TAILQ_HEAD(ctf_label_head, ctf_label);
#define CTF_LABEL_HEAD_SIZE sizeof(struct ctf_label_head)

char*
ctf_label_get_name (struct ctf_label *label);

uint32_t
ctf_label_get_index (struct ctf_label *label);

#endif

