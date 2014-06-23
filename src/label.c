#include "label.h"
#include "util/section.h"
#include "errors.h"

#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

char*
ctf_label_get_name (struct ctf_label *label)
{
	if (label != NULL)
		return label->name;
	else
		return NULL;
}

uint32_t
ctf_label_get_index (struct ctf_label *label)
{
	if (label != NULL)
		return label->index;
	else
		return 0;
}

