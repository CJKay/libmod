#ifndef LIBMOD_ERROR_H
#define LIBMOD_ERROR_H

typedef enum libmod_error {
	ENOERROR = 0,
	ENOHANDLE,
	ECOULDNTCLOSE,
	EBADMODULE,
	EBADMODULENAME,
	ENOMODULEEXPORTS,
	ETOOMANYMODULES,
	ENOSUCHMODULE,
	ENOSUCHFUNCTION
} libmod_error_t;

extern libmod_error_t libmod_error_number(void);
extern const char *libmod_error_string(libmod_error_t error);
extern const char *libmod_error_details(void);

extern void __libmod_error_clear(void);
extern libmod_error_t __libmod_error_setandret(libmod_error_t num, const char *str);

#endif /* LIBMOD_ERROR_H */
