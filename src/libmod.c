#include "../include/libmod/libmod.h"

#include "../include/libmod/defs.h"

#include <stddef.h>
#include <string.h>
#include <malloc.h>

int libmod_exit(int code) {
	__libmod_error_clear();

	return code;
}

char *libmod_strdup(const char *src) {
	size_t len;
	char *dest;

	len = strlen(src) + 1;
	if((dest = malloc(len)) == NULL)
		return(NULL);

	(void)memcpy(dest, src, len);

	return(dest);
}
