#include "int_float.h"

uint16_t
ctf_int_float_get_size (struct ctf_int_float *int_float)
{
	if (int_float)
		return int_float->size;
	else
		return 0;
}

uint8_t
ctf_int_float_get_offset (struct ctf_int_float *int_float)
{
	if (int_float)
		return int_float->offset;
	else
		return 0;
}

int
ctf_int_is_signed (struct ctf_int_float *int_float)
{
	if (int_float)
		return (int_float->encoding & CTF_INT_SIGNED);
	else
		return 0;
}

int
ctf_int_is_char (struct ctf_int_float *int_float)
{
	if (int_float)
		return (int_float->encoding & CTF_INT_CHAR);
	else
		return 0;
}

int
ctf_int_is_boolean (struct ctf_int_float *int_float)
{
	if (int_float)
		return (int_float->encoding & CTF_INT_BOOLEAN);
	else
		return 0;
}

int
ctf_int_is_varargs (struct ctf_int_float *int_float)
{
	if (int_float)
		return (int_float->encoding & CTF_INT_VARARGS);
	else
		return 0;
}

int
ctf_float_get_encoding (struct ctf_int_float *int_float)
{
	if (int_float)
		return int_float->encoding;
	else
		return 0;
}

