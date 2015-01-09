#include "type/struct_union.h"

_CTF_GET_PROPERTY_IMPL(
	ctf_struct_union_get_name,
	ctf_struct_union,
	char*,
	name)

_CTF_SET_PROPERTY_IMPL(
	ctf_struct_union_set_name,
	ctf_struct_union,
	char*,
	name)

_CTF_GET_PROPERTY_IMPL(
	ctf_struct_union_get_member_count,
	ctf_struct_union,
	ctf_count,
	member_count)

_CTF_LISTING_IMPL(
	ctf_struct_union_get_next_member, 
	ctf_struct_union,
	ctf_member,
	member_head,
	members)

_CTF_ADD_IMPL(
	ctf_struct_union_add_member,
	ctf_struct_union,
	ctf_member,
	member_head,
	members,
	member_count)

_CTF_FROM_TYPE_IMPL(
	ctf_struct_union_init,
	ctf_struct_union)

_CTF_CREATE_1_LIST_IMPL(
	ctf_struct_union_create,
	ctf_struct_union,
	CTF_STRUCT_UNION_SIZE,
	member_head,
	CTF_MEMBER_HEAD_SIZE,
	member_count)

size_t
ctf_struct_union_memory_usage (ctf_struct_union struct_union)
{
	size_t usage = 0;

	usage += CTF_STRUCT_UNION_SIZE;
	usage += strlen(struct_union->name);

	ctf_member runner;
	TAILQ_FOREACH (runner, struct_union->member_head, members)
	{
		usage += ctf_member_memory_usage(runner);
	}

	return usage;
}

