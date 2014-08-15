#ifndef CTF_SPACE_H
#define CTF_SPACE_H

/*
 * This header contains functions that are different in kernel-space and
 * user-space, hence the name. Using any of these macros anywhere in the code
 * should be fine. In case that there is no equivalent of the function in the
 * other space, the macro is translated to some no-op operation.
 */

#ifdef _KERNEL

	#define CTF_MALLOC(nbytes) malloc(nbytes, M_CTF, M_WAITOK)
	#define CTF_MALLOC_DECLARE(name) MALLOC_DECLARE(name)
	#define CTF_STRDUP(string) strdup(string, M_CTF)

#elif

	#define CTF_MALLOC(nbytes) malloc(nbytes)
	#define CTF_MALLOC_DECLARE(name) (void)0
	#define CTF_STRDUP(string) strdup(string)

#endif

