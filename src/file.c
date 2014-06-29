#include "file.h"

_CTF_GET_PROPERTY_IMPL(ctf_file_get_version, struct ctf_file*, int, version)
_CTF_GET_PROPERTY_IMPL(ctf_file_is_compressed, struct ctf_file*, int,
    compressed)
_CTF_GET_PROPERTY_IMPL(ctf_file_get_parent_file, struct ctf_file*, 
    struct ctf_file*, parent_file)

_CTF_LISTING_IMPL(ctf_file_get_next_label, struct ctf_file*, struct ctf_label*,
    label_head, labels);
_CTF_LISTING_IMPL(ctf_file_get_next_type, struct ctf_file*, struct ctf_type*,
    type_head, types);
_CTF_LISTING_IMPL(ctf_file_get_next_function, struct ctf_file*, 
    struct ctf_function*, function_head, functions);
_CTF_LISTING_IMPL(ctf_file_get_next_data_object, struct ctf_file*, 
    struct ctf_data_object*, data_object_head, data_objects);

