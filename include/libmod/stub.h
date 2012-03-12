#ifndef LIBMOD_STUB_H
#define LIBMOD_STUB_H

#include "version.h"
#include "exports.h"

typedef struct libmod_stub {
	const char *name;
	const char *description;

	libmod_version_t version;
	libmod_exports_t exports;
} libmod_stub_t;

#endif // LIBMOD_STUB_H
