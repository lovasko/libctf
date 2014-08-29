#include "errors.h"

const char *
ctf_get_error_string (int error)
{
	static const char *strings[] = 
	{
		"OK.", 
		"File not found.",
		"ELF header is corrupted.",
		"ELF version is wrong.",
		"Unable to open the ELF file.",
		"The '.SUNW_ctf' section was not found.",
		"The string table was not found.",
		"The symbol table was not found.",
		"Unable to decompress the data.",
		"Decompressed data is corrupted.",
		"Unable to find required label in the parent file.",
		"Wrong CTF magic number.",
		"Wrong CTF version.",
		"Label section is corrupted.",
		"Not found.",
		"End of the list.",
		"Null pointer.",
		"Sections offsets corrupted.",
		"Kind invalid.",
		"Type ID not found."
	};

	if (error < CTF_E_MIN || error > CTF_E_MAX)
		return "Unknown error.";
	else
		return strings[error];
}

