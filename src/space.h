#ifndef CTF_SPACE_H
#define CTF_SPACE_H

/*
 * This header contains functions that are different in kernel-space and
 * user-space, hence the name. Using any of these macros anywhere in the code
 * should be fine. In case that there is no equivalent of the function in the
 * other space, the macro is translated to some no-op operation.
 */

#ifdef _KERNEL

	#include <sys/libkern.h>
	#include <sys/malloc.h>
	#include <sys/systm.h>
	#include <sys/kernel.h>

	#define CTF_MALLOC(nbytes) malloc(nbytes, M_CTF, M_WAITOK)
	#define CTF_MALLOC_DECLARE() MALLOC_DECLARE(M_CTF)
	#define CTF_STRDUP(string) strdup(string, M_CTF)
	#define CTF_FREE(ptr) free(ptr, M_CTF)

#else

	#include <stdlib.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <string.h>

	#define CTF_MALLOC(nbytes) malloc(nbytes)
	#define CTF_MALLOC_DECLARE() 
	#define CTF_STRDUP(string) strdup(string)
	#define CTF_FREE(ptr) free(ptr)

#endif /* _KERNEL */

#endif

