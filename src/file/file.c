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

_CTF_FOREACH_IMPL(
	ctf_file_foreach_label,
	ctf_file,
	ctf_label,
	labels)

_CTF_COUNT_IMPL(
	ctf_file_get_label_count,
	ctf_file,
	labels)

_CTF_FOREACH_IMPL(
	ctf_file_foreach_type,
	ctf_file,
	ctf_type,
	types)

_CTF_COUNT_IMPL(
	ctf_file_get_type_count,
	ctf_file,
	types)

_CTF_FOREACH_IMPL(
	ctf_file_foreach_data_object,
	ctf_file,
	ctf_data_object,
	data_objects)

_CTF_COUNT_IMPL(
	ctf_file_get_data_object_count,
	ctf_file,
	data_objects)

_CTF_FOREACH_IMPL(
	ctf_file_foreach_function,
	ctf_file,
	ctf_function,
	function_objects)

_CTF_COUNT_IMPL(
	ctf_file_get_function_count,
	ctf_file,
	function_objects)

_CTF_CREATE_4_LIST_IMPL(
	ctf_file_create,
	ctf_file,
	CTF_FILE_SIZE,
	labels,
	types,
	data_objects,
	function_objects)

static size_t
label_memory_usage (ctf_file file)
{
	size_t usage;
	struct m_elem* runner;
	ctf_label label;

	usage = sizeof(struct m_list);

	m_list_first(&file->labels, &runner);
	while (runner != NULL)
	{
		m_elem_data(runner, (void**)&label);
		usage += ctf_label_memory_usage(label);

		m_elem_next(runner, &runner);
	}

	return usage;
}

static size_t
type_memory_usage (ctf_file file)
{
	size_t usage;
	struct m_elem* runner;
	ctf_type type;

	usage = sizeof(struct m_list);

	m_list_first(&file->types, &runner);
	while (runner != NULL)
	{
		m_elem_data(runner, (void**)&type);
		usage += CTF_TYPE_SIZE;

		switch (type->kind)
		{
			case CTF_KIND_INT:
				usage += ctf_int_memory_usage(type->data);
			break;

			case CTF_KIND_FLOAT:
				usage += ctf_float_memory_usage(type->data);
			break;

			case CTF_KIND_POINTER:
				usage += ctf_pointer_memory_usage(type->data);
			break;

			case CTF_KIND_ARRAY:
				usage += ctf_array_memory_usage(type->data);
			break;

			case CTF_KIND_FUNC:
				usage += ctf_function_memory_usage(type->data);
			break;

			/* FALL THROUGH */
			case CTF_KIND_UNION:
			case CTF_KIND_STRUCT:
				usage += ctf_struct_union_memory_usage(type->data);
			break;

			case CTF_KIND_ENUM:
				usage += ctf_enum_memory_usage(type->data);
			break;

			case CTF_KIND_FWD_DECL:
				usage += ctf_fwd_decl_memory_usage(type->data);
			break;

			case CTF_KIND_TYPEDEF:
				usage += ctf_typedef_memory_usage(type->data);
			break;
		}

		m_elem_next(runner, &runner);
	}

	return usage;
}

static size_t
data_object_memory_usage (ctf_file file)
{
	size_t usage;
	struct m_elem* runner;
	ctf_data_object data_object;

	usage = sizeof(struct m_list);

	m_list_first(&file->data_objects, &runner);
	while (runner != NULL)
	{
		m_elem_data(runner, (void**)&data_object);
		usage += CTF_DATA_OBJECT_SIZE;
		usage += strlen(data_object->name);

		m_elem_next(runner, &runner);
	}

	return usage;
}

static size_t
function_memory_usage (ctf_file file)
{
	size_t usage;
	struct m_elem* runner;
	ctf_function function;

	usage = sizeof(struct m_list);

	m_list_first(&file->function_objects, &runner);
	while (runner != NULL)
	{
		m_elem_data(runner, (void**)&function);
		usage += ctf_function_memory_usage(function);
		m_elem_next(runner, &runner);
	}

	return usage;
}

size_t
ctf_file_memory_usage (ctf_file file)
{
	size_t usage;

	usage = CTF_FILE_SIZE;
	usage += sizeof(ctf_type) * file->type_count;
	usage += strlen(file->path_basename);

	usage += label_memory_usage(file);
	usage += type_memory_usage(file);
	usage += data_object_memory_usage(file);
	usage += function_memory_usage(file);

	return usage;
}

