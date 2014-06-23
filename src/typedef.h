#ifndef CTF_TYPEDEF_H
#define CTF_TYPEDEF_H

struct ctf_typedef
{
	char *name;
	struct ctf_type *type;
};
#define CTF_TYPEDEF_SIZE sizeof(struct ctf_typedef)

int
ctf_typedef_get_name (struct ctf_typedef *_typedef, char **out_name);

int
ctf_typedef_get_type (struct ctf_typedef *_typedef, struct ctf_type **out_type);

#endif

