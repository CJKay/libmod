#ifndef LIBMOD_EXPORTS_H
#define LIBMOD_EXPORTS_H

#include "function.h"
#include "defs.h"

typedef struct libmod_exports {
	const unsigned int count;
	const libmod_function_t functions[LIBMOD_MAXEXPORTS];
} libmod_exports_t;

#endif /* LIBMOD_EXPORTS_H */
