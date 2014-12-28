#include <sys/queue.h>

#include "file/file.h"

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

_CTF_LISTING_IMPL(
	ctf_file_get_next_type,
	ctf_file,
	ctf_type,
	type_head,
	types)

_CTF_LISTING_IMPL(
	ctf_file_get_next_function,
	ctf_file, ctf_function,
	function_head,
	functions);

_CTF_LISTING_IMPL(
	ctf_file_get_next_data_object,
	ctf_file,
	ctf_data_object,
	data_object_head,
	data_objects);

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

