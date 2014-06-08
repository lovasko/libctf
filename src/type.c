#include "type.h"
#include "kind.h"
#include "vardata.h"
#include "array.h"
#include "member.h"
#include "enum.h"

static struct ctf_type*
lookup_type (struct ctf_file *file, uint16_t id)
{
	if (id < file->type_id_offset)
	{
		if (file->parent_file != NULL)
			return lookup_type(file->parent_file, id);
		else
			return NULL;
	}
	else
		return file->type_id_table[id];	
}

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
int
read_types (struct ctf_type_head *head, struct _section *section, struct
    _strings *strings)
{
	uint64_t offset = 0;	
	uint16_t id = 0;

	struct ctf_type **id_table;
	/* 
	 * Instead of reallocating the array all the time, I chose a way to estimate
	 * the size of the type count: we need to assure, that we will never
	 * index-overflow the array and that means that the worst case is that all
	 * types are small_types with no addition variant data. This formula is for
	 * now the best solution with the simplicity/power ratio. We will see in
	 * future, whether it is accurate enough, or we need to really reallocate the
	 * array now and then.
	 */
	unsigned int type_count_estimate = section->size / _CTF_SMALL_TYPE_SIZE;
	id_table = malloc(type_count_estimate * CTF_TYPE_SIZE);

	while (offset < section->size)
	{
		printf("Parsing next type, offset = %d\n", offset);
		struct _ctf_small_type *small_type = section->data + offset;	
		uint8_t kind = ctf_kind_from_info(small_type->info);
		uint16_t vardata_length = small_type->info & CTF_VARDATA_LENGTH_MAX;
		printf("kind = %s, vardata_length = %d\n", ctf_kind_to_string(kind),
		    vardata_length);

		struct ctf_type *type = malloc(CTF_TYPE_SIZE);			
		type->kind = kind;
		id_table[id++] = type;

		if (ctf_kind_is_pure_reference(kind) == 1)
		{
			if (kind == CTF_KIND_TYPEDEF)
				type->name = strdup(strings_lookup(strings, small_type->name));
			else
				type->name = NULL;

			if (small_type->type < 0 || small_type->type > id)
				return 1;
			type->data = id_table[small_type->type];

			offset += _CTF_SMALL_TYPE_SIZE;
		}

		if (ctf_kind_is_special(kind) == 1)
		{
			type->name = NULL;
			type->data = NULL;

			offset += _CTF_SMALL_TYPE_SIZE;
		}

		if (ctf_kind_is_complex(kind) == 1 && kind != CTF_KIND_FUNC)
		{
			uint64_t advance = _CTF_SMALL_TYPE_SIZE;
			if (small_type->size > CTF_SMALL_TYPE_THRESHOLD)
			{
				struct _ctf_large_type *large_type = section->data + offset;
				advance	+= (_CTF_LARGE_TYPE_SIZE - _CTF_SMALL_TYPE_SIZE);
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
					type->data = read_array_vardata(section->data + offset, id_table);
					offset += _CTF_ARRAY_SIZE;
				break;

				case CTF_KIND_ENUM:
					type->data = read_enum_vardata(section->data + offset, vardata_length);
					offset += vardata_length * _CTF_ENUM_ENTRY_SIZE;
				break;

				case CTF_KIND_STRUCT:
				case CTF_KIND_UNION:
					type->data = read_struct_union_vardata(section->data + offset,
					    id_table, vardata_length, small_type->size);
					offset += vardata_length * (small_type->size > CTF_MEMBER_THRESHOLD ? 
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

			struct ctf_type *return_type = id_table[small_type->type];
			type->name = strdup(strings_lookup(strings, small_type->name));
			type->data = read_function_vardata(section->data + offset, id_table,
			    vardata_length, return_type);

			offset += (vardata_length + (vardata_length & 1)) * sizeof(uint16_t);

			unsigned char *to_print = (unsigned char*)(section->data + offset);
			for (unsigned int i = 0; i < 20; i++)
				printf("%02X ", to_print[i]);
		}

		LIST_INSERT_HEAD(head, type, types);

		printf("%s\n\n", type->name);
	}

	return 0;
}

