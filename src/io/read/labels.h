#ifndef CTF_READ_LABELS_H
#define CTF_READ_LABELS_H

#include "io/read/strings.h"
#include "file/file.h"
#include "util/section.h"

/**
 * Parse the label section of the CTF data.
 *
 * Labels are stored as a set of consecutive binary blobs that are 
 * identical to content of the struct _ctf_label.
 * 
 * @param file CTF data
 * @param section section holding the raw-label related CTF data
 * @param strings table to resolve strings
 * @return CTF_OK on success, one of CTF_E_* otherwise
 */
int
_ctf_read_labels (struct ctf_file* file, struct _section* section, 
    struct _strings* strings);

#endif

