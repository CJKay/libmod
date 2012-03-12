#include "../include/libmod/module.h"

#include "../include/libmod/error.h"
#include "../include/libmod/application.h"
#include "../include/libmod/defs.h"
#include "../include/libmod/libmod.h"

#if defined(LIBMOD_UNIX)
#include <dlfcn.h>
#elif defined(LIBMOD_WINDOWS)
#include <windows.h>
#endif

#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

libmod_module_handle_t __libmod_module_gethandle(const char *filename) {
	assert(filename != NULL);

	libmod_module_handle_t handle;

#if defined(LIBMOD_UNIX)
	handle = dlopen(filename, RTLD_NOW | RTLD_GLOBAL);
	if(handle == NULL) {
		__libmod_error_setandret(ENOHANDLE, dlerror());

		return NULL;
	}
#elif defined(LIBMOD_WINDOWS)
	handle = LoadLibrary(filename);
	if(handle == NULL) {
		LPVOID errstr = (LPVOID)libmod_error_details();
		if(!FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
			    FORMAT_MESSAGE_FROM_SYSTEM |
			    FORMAT_MESSAGE_IGNORE_INSERTS,
			    NULL,
			    GetLastError(),
			    0,
			    (LPTSTR)&errstr,
			    0,
			    NULL
		)) {
			__libmod_error_setandret(ENOHANDLE, NULL);
		} else {
			__libmod_error_setandret(ENOHANDLE, errstr); // TODO: Get the actual error, find a way of freeing the string afterwards too
		}
	}
#endif

	return handle;
}

libmod_module_t *__libmod_module_checkvalidity(libmod_module_handle_t handle) {
	assert(handle != NULL);

	libmod_module_t *module;

#if defined(LIBMOD_UNIX)
	module = dlsym(handle, "libmod_module");
	if(module == NULL) {
		__libmod_error_setandret(EBADMODULE, dlerror());

		return NULL;
	}
#elif defined(LIBMOD_WINDOWS)
	module = (libmod_module_t *)GetProcAddress(handle, "libmod_module");
	if(module == NULL) {
		__libmod_error_setandret(EBADMODULE, NULL);

		return NULL;
	}
#endif

	if(module->stub.name == NULL || strlen(module->stub.name) == 0) {
		__libmod_error_setandret(EBADMODULENAME, libmod_strdup(module->stub.name));
		__libmod_module_closehandle(handle);

		return NULL;
	}

	if(module->stub.exports.count == 0) {
		__libmod_error_setandret(ENOMODULEEXPORTS, libmod_strdup(module->stub.name));
		__libmod_module_closehandle(handle);

		return NULL;
	}

	return module;
}

libmod_error_t __libmod_module_closehandle(libmod_module_handle_t handle) {
	assert(handle != NULL);

#if defined(LIBMOD_UNIX)
	if(dlclose(handle) != 0)
		return __libmod_error_setandret(ECOULDNTCLOSE, dlerror());
#elif defined(LIBMOD_WINDOWS)
	if(!FreeLibrary(handle))
		return __libmod_error_setandret(ECOULDNTCLOSE, NULL);
#endif

	return ENOERROR;
}

libmod_module_t *libmod_module_load(libmod_application_t *application, const char *filename) {
	assert(application != NULL && filename != NULL);

	libmod_module_handle_t handle = __libmod_module_gethandle(filename);

	if(handle == NULL)
		return NULL;

	libmod_module_t *module = __libmod_module_checkvalidity(handle);
	if(module == NULL)
		return NULL;

	module->application = application;
	module->filename = filename;
	module->handle = handle;

	application->modules.module[application->modules.count] = module;
	application->modules.count++;

	return module;
}

libmod_error_t libmod_module_unload(libmod_application_t *application, libmod_module_t *module) {
	assert(application != NULL && module != NULL);

	libmod_error_t error;

	if((error = __libmod_module_closehandle(module->handle)) != ENOERROR)
		return error;

	memmove(&application->modules.module[application->modules.count - 1], &application->modules.module[application->modules.count], (LIBMOD_MAXMODULES) - application->modules.count);
	application->modules.count--;

	return ENOERROR;
}

libmod_module_t *libmod_module_fromfilename(libmod_application_t *application, const char *filename) {
	for(uint64_t i = 0; i < application->modules.count; i++) {
		if(strcmp(application->modules.module[i]->filename, filename) == 0) {
			return application->modules.module[i];
		}
	}

	return NULL;
}

libmod_module_t *libmod_module_fromname(libmod_application_t *application, const char *filename) {
	for(uint64_t i = 0; i < application->modules.count; i++) {
		if(strcmp(application->modules.module[i]->stub.name, filename) == 0) {
			return application->modules.module[i];
		}
	}

	return NULL;
}
