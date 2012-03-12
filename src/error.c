#include "../include/libmod/error.h"

static libmod_error_t __libmod_errno;
static const char *__libmod_errstr;

const char *__libmod_error_strings[] = {
	[ENOERROR] = "No error",
	[ENOHANDLE] = "Couldn't get handle for file",
	[ECOULDNTCLOSE] = "Couldn't close handle for file",
	[EBADMODULE] = "Missing module definition in file",
	[EBADMODULENAME] = "Module contains a missing or bad name",
	[ENOMODULEEXPORTS] = "Module does not define any exports",
	[ETOOMANYMODULES] = "Application has reached maximum number of modules",
	[ENOSUCHMODULE] = "No such module in application",
	[ENOSUCHFUNCTION] = "No such function in stub"
};

libmod_error_t libmod_error_number(void) {
	return __libmod_errno;
}

const char *libmod_error_string(libmod_error_t error) {
	return __libmod_error_strings[error];
}

const char *libmod_error_details(void) {
	return __libmod_errstr;
}

void __libmod_error_clear(void) {
#if defined(LIBMOD_WINDOWS)
	if(__libmod_errstr != NULL)
		LocalFree(error);
#elif defined(LIBMOD_UNIX)
	if(__libmod_errstr != NULL)
		free(error);
#endif
}

libmod_error_t __libmod_error_setandret(libmod_error_t num, const char *str) {
	__libmod_error_clear();
	__libmod_errno = num;
	__libmod_errstr = str;
	return num;
}
