#ifndef LIBMOD_MODULES_H
#define LIBMOD_MODULES_H

#include "defs.h"

typedef struct libmod_module libmod_module_t;

typedef struct libmod_modules {
	unsigned int count;
	libmod_module_t *module[LIBMOD_MAXMODULES];
} libmod_modules_t;

#endif /* LIBMOD_MODULES_H */
