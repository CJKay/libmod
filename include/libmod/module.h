#ifndef LIBMOD_MODULE_H
#define LIBMOD_MODULE_H

#include "defs.h"
#include "stub.h"
#include "error.h"

#if defined(LIBMOD_UNIX)
typedef	void * libmod_module_handle_t;
#elif defined(LIBMOD_WINDOWS)
#include <windows.h>

typedef HMODULE libmod_module_handle_t;
#endif

typedef struct libmod_application libmod_application_t;

typedef struct libmod_module {
	libmod_stub_t stub;
	libmod_application_t *application;
	libmod_module_handle_t handle;
	const char *filename;
} libmod_module_t;

extern libmod_module_handle_t __libmod_module_gethandle(const char *filename);
extern libmod_module_t *__libmod_module_checkvalidity(libmod_module_handle_t handle);
extern libmod_error_t __libmod_module_closehandle(libmod_module_handle_t handle);
extern libmod_module_t *libmod_module_load(libmod_application_t *application, const char *filename);
extern libmod_error_t libmod_module_unload(libmod_application_t *application, libmod_module_t *module);
extern libmod_module_t *libmod_module_fromfilename(libmod_application_t *application, const char *filename);

#endif // LIBMOD_MODULE_H
