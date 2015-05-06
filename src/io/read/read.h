#ifndef CTF_READ_READ_H
#define CTF_READ_READ_H

#include "file/errors.h"
#include "file/file.h"
#include "object/data/data_object.h"
#include "object/function/function.h"
#include "object/function/argument.h"
#include "space.h"
#include "type/array.h"
#include "type/enum.h"
#include "type/enum_entry.h"
#include "type/float.h"
#include "type/fwd_decl.h"
#include "type/info.h"
#include "type/int.h"
#include "type/kind.h"
#include "type/pointer.h"
#include "type/struct_union.h"
#include "type/typedef.h"
#include "util/section.h"
#include "version.h"

struct ctf_file;

/**
 * Value of the first two bytes has to match this constant.
 */
#define _CTF_MAGIC 0xCFF1

#define _CTF_FLAG_COMPRESSED 0x1

/**
 * Binary reflection of the preface of the CTF header.
 *
 * The preface is never compressed or anyhow affected. 
 * Designated for internal use only.
 *
 * Flags:
 * 0x1 = compressed
 */
struct _ctf_preface
{
	uint16_t magic; /**< magic number identifying the format (see CTF_MAGIC) */
	uint8_t version; /**< version indicator */
	uint8_t flags; /**< flags (see the struct description) */
};

/**
 * Binary reflection of the CTF header.
 *
 * Note that all the offsets are starting just after this header. E.g. even
 * though the label_offset is 0, it still means that you have to look at the 0
 * + _CTF_HEADER_SIZE. 
 * Designated for internal use only.
 */
struct _ctf_header
{
	struct _ctf_preface preface; /**< the preface */

	uint32_t parent_label; /**< reference to the parent label */
	uint32_t parent_basename; /**< reference to the parent basename */

	uint32_t label_offset; /**< offset of the label section */
	uint32_t object_offset; /**< offset of the object section */
	uint32_t function_offset; /**< offset of the function section */
	uint32_t type_offset; /**< offset of the type section */

	uint32_t string_offset; /**< offset of the internal string table */
	uint32_t string_length; /**< length of the internal string table */
};
#define _CTF_HEADER_SIZE sizeof(struct _ctf_header)

/**
 * Tuple holding pointers to two string tables: ELF and CTF.
 */
struct _strings
{
	struct _section* ctf;
	struct _section* elf;
};

/**
 * Check the header preface for expected values (magic number, version, ...).
 *
 * @param preface header preface
 * @return CTF_OK on success, one of CTF_E_* otherwise
 */
int
_ctf_preface_check (struct _ctf_preface* preface);

/**
 * Check if section offsets are sorted correctly.
 * 
 * The correct order:
 *  - labels 
 *  - objects
 *  - functions
 *  - types 
 *  - string table
 *
 * @param header header
 * @return CTF_OK on success, CTF_E_OFFSETS_CORRUPT otherwise
 */
int
_ctf_header_offset_sanity_check (struct _ctf_header* header);

/**
 * Read int variable data.
 *
 * Int variable data is stored as 4 bytes:
 *  - 1. byte = content (see CTF_INT_CONTENT_*)
 *  - 2. byte = offset in bits
 *  - 3. and 4. byte = size in bits
 *
 * @param data pointer to start of the variable data
 * @return parsed ctf_int
 */
struct ctf_int*
_ctf_read_int_vardata (void* data);

/**
 * Read float variable data.
 *
 * Float variable data is stored as 4 bytes:
 *  - 1. byte = encoding (see CTF_FLOAT_ENCODING_*)
 *  - 2. byte = offset in bits
 *  - 3. and 4. byte = size in bits
 *
 * @param data pointer to start of the variable data
 * @return parsed ctf_float
 */
struct ctf_float*
_ctf_read_float_vardata (void* data);

/**
 * Read the array variable data.
 * 
 * The array variable data is the binary reflection of the _ctf_array struct.
 * It is exactly _CTF_ARRAY_SIZE bytes long.
 * 
 * @param data start of the variable data
 * @return pointer to filled ctf_array struct
 */
struct ctf_array*
_ctf_read_array_vardata (void* data);

/**
 * Read the function variable data.
 *
 * The function variable data is a list of uint16_t which are type IDs. 
 * Length of the list is the length parameter. The actual length of 
 * the variable data is always an even number, even if the
 * argument count is odd. This is already adjusted in the calling function.
 * 
 * @param data start of the variable data
 * @param length number of the arguments 
 * @return pointer to filled ctf_function struct
 */
struct ctf_argument_head*
_ctf_read_function_vardata (void* data, uint16_t length);

/**
 * Read the enum variable data.
 *
 * The enum variable data is a length-long list of binary reflections of the
 * _ctf_enum_entry structs.
 *
 * @param data start of the variable data
 * @param length number of enum entries
 * @return pointer to filled ctf_enum_head struct
 */
struct ctf_enum_head*
_ctf_read_enum_vardata (void* data, uint16_t length, struct _strings* strings);

/**
 * Read the struct/union variable data.
 *
 * Both, the struct and the union, have identical variable data. Based on the
 * value of the size parameter (threshold is the CTF_MEMBER_THRESHOLD), the
 * variable list composed of either small_member entries or large_member
 * entires.
 *
 * @param data start of the variable data
 * @param length number of the member entries (oblivious to the member size)
 * @param size size of the vardata in bytes
 * @param strings string resolvation tables
 * @return pointer to filled ctf_member_head struct
 */
struct ctf_member_head*
_ctf_read_struct_union_vardata (void* data, uint16_t length, uint64_t size, 
    struct _strings* strings);

/**
 * Look up a string identified by the reference from either ELF or CTF string
 * table.
 *
 * @param strings tuple of string tables
 * @param reference string reference
 * @return pointer to NULL-terminated const string 
 */
const char*
_ctf_strings_lookup (
		struct _strings* strings,
		uint32_t reference);

/**
 * Parse function and data objects with the help from the symbol table.
 *
 * @param file
 * @param symtab_section 
 * @param object_section 
 * @param function_section
 * @param strings 
 * @return CTF_OK on success, one of CTF_E_* otherwise
 */
int
_ctf_read_functions_and_objects (
    struct ctf_file* file, 
		struct _section* symtab_section, 
		struct _section* object_section, 
		struct _section* function_section, 
		struct _strings* strings);

/**
 * Parse data section containing CTF types.
 *
 * All type data is stored as generic type header (either small or large),
 * and some kinds of types (like enums, functions or floats) contain
 * consecutive variable data section, describing needed details of the 
 * type in question. More on the exact algorithm in the types.c and on the
 * variable data in vardata.h/.c.
 *
 * @param file CTF data
 * @param section section holding the type information
 * @param strings tables to help name resolving
 * @return CTF_OK on success, one of CTF_E_* otherwise
 */
int
_ctf_read_types (
		struct ctf_file* file,
		struct _section* section, 
    struct _strings* strings);

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
_ctf_read_labels (
		struct ctf_file* file,
		struct _section* section, 
    struct _strings* strings);

/**
 * Look up a type based on its ID.
 * 
 * @param file CTF data to use
 * @param id type ID
 * @return type on success, NULL otherwise
 */
struct ctf_type*
_ctf_lookup_type (
		struct ctf_file* file,
		uint16_t id);

#ifndef _KERNEL
/**
 * Perform a ZIP decompression on a data section.
 *
 * @param to_decompress data section to decompress
 * @return decompressed data
 */
struct _section*
_ctf_decompress (struct _section* to_decompress);
#endif

/**
 * Parse the raw uncompressed CTF data.
 *
 * @param [in] ctf_data uncompressed CTF data (also with header)
 * @param [in] symbol_table symbol table of the ELF object
 * @param [in] string_table string table of the ELF object
 * @param [out] file parsed CTF data
 * @return CTF_OK on success, one of CTF_E_* otherwise
 */
int
ctf_file_read_data (
    const char* filename,
    struct _section* ctf_data, 
    struct _section* symbol_table, 
    struct _section* string_table,
    ctf_file* result);

#ifndef _KERNEL

/**
 * Parse the file and extract all CTF data.
 * 
 * @param [in] filename filename
 * @param [out] file parsed CTF data
 * @return CTF_OK on success, one of CTF_E_* otherwise
 */
int
ctf_file_read (const char* filename, ctf_file* file);

#endif /* not _KERNEL */

#endif

