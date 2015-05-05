#include <sys/queue.h>

#include "file/file.h"
#include "object/function/function.h"
#include "type/array.h"
#include "type/enum.h"
#include "type/float.h"
#include "type/fwd_decl.h"
#include "type/int.h"
#include "type/pointer.h"
#include "type/struct_union.h"
#include "type/typedef.h"

_CTF_GET_PROPERTY_IMPL(
	ctf_file_get_version,
	ctf_file,
	ctf_version,
	version)

_CTF_SET_PROPERTY_IMPL(
	ctf_file_set_version,
	ctf_file,
	ctf_version,
	version)

_CTF_GET_PROPERTY_IMPL(
	ctf_file_get_is_compressed,
	ctf_file,
	uint8_t,
	is_compressed)

_CTF_SET_PROPERTY_IMPL(
	ctf_file_set_is_compressed,
	ctf_file,
	uint8_t,
	is_compressed)

_CTF_GET_PROPERTY_IMPL(
	ctf_file_get_parent_file,
	ctf_file,
	ctf_file,
	parent_file)

_CTF_SET_PROPERTY_IMPL(
	ctf_file_set_parent_file,
	ctf_file,
	ctf_file,
	parent_file)

_CTF_GET_PROPERTY_IMPL(
	ctf_file_get_basename,
	ctf_file,
	char*,
	path_basename)

_CTF_SET_PROPERTY_IMPL(
	ctf_file_set_basename,
	ctf_file,
	char*,
	path_basename)

_CTF_LISTING_IMPL(
	ctf_file_get_next_label,
	ctf_file,
	ctf_label,
	label_head,
	labels)

_CTF_FOREACH_IMPL(
	ctf_file_foreach_label,
	ctf_file,
	ctf_label,
	ctf_file_get_next_label)

_CTF_GET_PROPERTY_IMPL(
	ctf_file_get_type_count,
	ctf_file,
	ctf_count,
	type_count)

_CTF_LISTING_IMPL(
	ctf_file_get_next_type,
	ctf_file,
	ctf_type,
	type_head,
	types)

_CTF_FOREACH_IMPL(
	ctf_file_foreach_type,
	ctf_file,
	ctf_type,
	ctf_file_get_next_type)

_CTF_LISTING_IMPL(
	ctf_file_get_next_function,
	ctf_file, ctf_function,
	function_head,
	functions)

_CTF_FOREACH_IMPL(
	ctf_file_foreach_function,
	ctf_file,
	ctf_function,
	ctf_file_get_next_function)

_CTF_LISTING_IMPL(
	ctf_file_get_next_data_object,
	ctf_file,
	ctf_data_object,
	data_object_head,
	data_objects)

_CTF_FOREACH_IMPL(
	ctf_file_foreach_data_object,
	ctf_file,
	ctf_data_object,
	ctf_file_get_next_data_object)

_CTF_CREATE_4_LIST_IMPL(
	ctf_file_create,
	ctf_file,
	CTF_FILE_SIZE,
	label_head,
	label_count,
	type_head,
	type_count,
	data_object_head,
	data_object_count,
	function_head,
	function_count)

static size_t
label_memory_usage (ctf_file file)
{
	size_t usage = 0;

	usage += CTF_LABEL_HEAD_SIZE;

	ctf_label runner;
	TAILQ_FOREACH (runner, file->label_head, labels)
	{
		usage += ctf_label_memory_usage(runner);
	}

	return usage;
}

static size_t
type_memory_usage (ctf_file file)
{
	size_t usage = 0;

	usage += CTF_TYPE_HEAD_SIZE;

	ctf_type runner;
	TAILQ_FOREACH (runner, file->type_head, types)
	{
		usage += CTF_TYPE_SIZE;

		switch (runner->kind)
		{
			case CTF_KIND_INT:
				usage += ctf_int_memory_usage(runner->data);
			break;

			case CTF_KIND_FLOAT:
				usage += ctf_float_memory_usage(runner->data);
			break;

			case CTF_KIND_POINTER:
				usage += ctf_pointer_memory_usage(runner->data);
			break;

			case CTF_KIND_ARRAY:
				usage += ctf_array_memory_usage(runner->data);
			break;

			case CTF_KIND_FUNC:
				usage += ctf_function_memory_usage(runner->data);
			break;

			/* FALL THROUGH */
			case CTF_KIND_UNION:
			case CTF_KIND_STRUCT:
				usage += ctf_struct_union_memory_usage(runner->data);
			break;

			case CTF_KIND_ENUM:
				usage += ctf_enum_memory_usage(runner->data);
			break;

			case CTF_KIND_FWD_DECL:
				usage += ctf_fwd_decl_memory_usage(runner->data);
			break;

			case CTF_KIND_TYPEDEF:
				usage += ctf_typedef_memory_usage(runner->data);
			break;
		}
	}

	return usage;
}

static size_t
data_object_memory_usage (ctf_file file)
{
	size_t usage = 0;

	usage += CTF_DATA_OBJECT_HEAD_SIZE;

	ctf_data_object runner;
	TAILQ_FOREACH (runner, file->data_object_head, data_objects)
	{
		usage += CTF_DATA_OBJECT_SIZE;
		usage += strlen(runner->name);
	}

	return usage;
}

static size_t
function_memory_usage (ctf_file file)
{
	size_t usage = 0;

	usage += CTF_FUNCTION_HEAD_SIZE;

	ctf_function runner;
	TAILQ_FOREACH (runner, file->function_head, functions)
	{
		usage += ctf_function_memory_usage(runner);
	}

	return usage;
}

size_t
ctf_file_memory_usage (ctf_file file)
{
	size_t usage = 0;

	usage += CTF_FILE_SIZE;
	usage += sizeof(ctf_type) * file->type_count;
	usage += strlen(file->path_basename);

	usage += label_memory_usage(file);
	usage += type_memory_usage(file);
	usage += data_object_memory_usage(file);
	usage += function_memory_usage(file);

	return usage;
}

