#include "type.h"
#include "file.h"
#include "kind.h"
#include "vardata.h"
#include "array.h"
#include "member.h"
#include "enum.h"
#include "function.h"

#include <string.h>


/*
 * Algorithm
 *
 * Assume that the type under the pointer is small_type. Examine the kind of
 * the type: if it is pure reference kind = POINTER, TYPEDEF, VOLATILE, CONST,
 * RESTRICT or one of the special kinds = FORWARD or NONE, there is no need to
 * bring the large_type to the game. The data member of the ctf_type struct
 * will simply point to another ctf_type. This pointer will be acquired from
 * the "ID to pointer table". Each type that is read gets an incrementing
 * unique integer ID. Therefore, if e.g. a TYPEDEF says that the reference type
 * is 15, we need to look into our "ID to pointer table" at index 15 and just
 * return the pointer. This introduces potential problem: what if there is a
 * forward reference? For now, we hope there is no such thing. Future
 * implementation might put these types aside, still recording them into the
 * "ID to pointer table" and create some type of waiting queue that awaits its
 * forward reference/base type.
 * In case of other, more complex types INT, FLOAT, ARRAY, FUNC, STRUCT, UNION
 * or ENUM, we need to check the size member (the type has no meaningful value)
 * and decide, based on the comparison with the CTF_TYPE_THRESHOLD, whether to
 * use the large_type. Afterwards, we need to read the variant data following
 * the type data. This, as the name suggests, varies for every kind - we need a
 * special function for every kind.
 */

static int
solve_type_references (struct ctf_file *file)
{
	struct ctf_type *type;
	LIST_FOREACH (type, file->type_head, types)
	{
		if (ctf_kind_is_pure_reference(type->kind) == 1)
		{
			type->data = lookup_type(file, type->type_reference);
		}

		if (type->kind == CTF_KIND_ARRAY)
		{
			struct ctf_array *array = type->data;
			array->type = lookup_type(file, array->type_reference);
		}

		if (type->kind == CTF_KIND_STRUCT || type->kind == CTF_KIND_UNION)
		{
			struct ctf_member_head *member_head = type->data;
			struct ctf_member *member;
			LIST_FOREACH (member, member_head, members)
			{
				member->type = lookup_type(file, member->type_reference);
			}
		}

		if (type->kind == CTF_KIND_FUNC)
		{
			struct ctf_function *func = type->data;
			func->return_type = lookup_type(file, func->return_type_reference);

			struct ctf_argument *argument;
			LIST_FOREACH (argument, func->argument_head, arguments)
			{
				argument->type = lookup_type(file, argument->type_reference);
			}
		}
	}

	return 0;
}

static int
create_type_table (struct ctf_file *file)
{
	file->type_id_table = malloc(CTF_TYPE_SIZE * (file->type_count + 1));

	struct ctf_type *type;
	LIST_FOREACH (type, file->type_head, types)
	{
		file->type_id_table[type->id] = type;	
	}

	return 0;
}

int
read_types (struct ctf_file *file, struct _section *section, struct
    _strings *strings)
{
	uint64_t offset = 0;	
	uint16_t id = 0;

	file->type_head = malloc(CTF_TYPE_HEAD_SIZE);
	LIST_INIT(file->type_head);

	file->type_count = 0;
	while (offset < section->size)
	{
		file->type_count++;

		printf("(%d) Parsing next type, offset = %d\n", id, offset);
		struct _ctf_small_type *small_type = section->data + offset;	
		uint8_t kind = ctf_kind_from_info(small_type->info);
		uint16_t vardata_length = small_type->info & CTF_VARDATA_LENGTH_MAX;
		printf("kind = %s, vardata_length = %d\n", ctf_kind_to_string(kind),
		    vardata_length);

		struct ctf_type *type = malloc(CTF_TYPE_SIZE);			
		type->kind = kind;
		type->id = id;

		unsigned char *to_print = (unsigned char*)(section->data + offset);
		for (unsigned int i = 0; i < 20; i++)
			printf("%02X ", to_print[i]);

		printf("small_type->name = %d\n", small_type->name);
		printf("small_type->info = %x\n", small_type->info);

		id++;

		if (ctf_kind_is_pure_reference(kind) == 1)
		{
			if (kind == CTF_KIND_TYPEDEF)
				type->name = strdup(strings_lookup(strings, small_type->name));
			else
				type->name = NULL;

			type->type_reference = small_type->type;

			offset += _CTF_SMALL_TYPE_SIZE;
		}

		if (kind == CTF_KIND_NONE)
		{
			type->name = NULL;
			type->data = NULL;

			offset += _CTF_SMALL_TYPE_SIZE;
		}

		if (kind == CTF_KIND_FWD_DECL)
		{
			type->name = strdup(strings_lookup(strings, small_type->name));		
			type->type_reference = small_type->type;

			offset += _CTF_SMALL_TYPE_SIZE;
		}

		if (ctf_kind_is_complex(kind) == 1 && kind != CTF_KIND_FUNC)
		{
			uint64_t advance = _CTF_SMALL_TYPE_SIZE;
			uint16_t size = small_type->size;
			printf("size = %d\n", size);
			if (small_type->size > CTF_SMALL_TYPE_THRESHOLD)
			{
				struct _ctf_large_type *large_type = section->data + offset;
				size = large_type->size;
				advance	+= (_CTF_LARGE_TYPE_SIZE - _CTF_SMALL_TYPE_SIZE);
				printf("Using the large type.\n");
			}
			offset += advance;

			type->name = strdup(strings_lookup(strings, small_type->name));

			switch (kind)
			{
				case CTF_KIND_INT:
				case CTF_KIND_FLOAT:
					type->data = read_int_float_vardata(section->data + offset);
					offset += 4;
				break;

				case CTF_KIND_ARRAY:
					type->data = read_array_vardata(section->data + offset);
					offset += _CTF_ARRAY_SIZE;
				break;

				case CTF_KIND_ENUM:
					type->data = read_enum_vardata(section->data + offset, vardata_length);
					offset += vardata_length * _CTF_ENUM_ENTRY_SIZE;
				break;

				case CTF_KIND_STRUCT:
				case CTF_KIND_UNION:
					type->data = read_struct_union_vardata(section->data + offset,
					    vardata_length, size);
					offset += vardata_length * (small_type->size >= CTF_MEMBER_THRESHOLD ? 
					    _CTF_LARGE_MEMBER_SIZE : _CTF_SMALL_MEMBER_SIZE);
				break;
			}
		}

		/* 
		 * We need to handle the function type with special touch, since it is a
		 * combination of both reference and complex type: it uses rather type then
		 * size from the small_type union but still needs additional parsing of the
		 * vardata. But we can not afford to check the type against the
		 * SMALL_TYPE_THRESHOLD and potentially load the large_type, which would
		 * make us skip either 4 arguments or even cut the header of next type.
		 */
		if (kind == CTF_KIND_FUNC)
		{
			offset += _CTF_SMALL_TYPE_SIZE;

			type->name = strdup(strings_lookup(strings, small_type->name));
			type->data = read_function_vardata(section->data + offset, vardata_length);

			((struct ctf_function*)type->data)->return_type_reference = 
			    small_type->type;

			offset += (vardata_length + (vardata_length & 1)) * sizeof(uint16_t);

			unsigned char *to_print = (unsigned char*)(section->data + offset);
			for (unsigned int i = 0; i < 20; i++)
				printf("%02X ", to_print[i]);
		}

		printf("Adding with ID %d.\n", type->id);
		LIST_INSERT_HEAD(file->type_head, type, types);

		printf("%s\n\n", type->name);
	}

	printf("type_count = %d\n", file->type_count);

	create_type_table(file);
	solve_type_references(file);

	return 0;
}

