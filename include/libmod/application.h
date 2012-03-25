#ifndef LIBMOD_APPLICATION_H
#define LIBMOD_APPLICATION_H

#include "stub.h"
#include "modules.h"

typedef struct libmod_application {
	libmod_stub_t stub;
	libmod_modules_t modules;
} libmod_application_t;

#endif /* LIBMOD_APPLICATION_H */
