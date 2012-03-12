#ifndef LIBMOD_FUNCTION_H
#define LIBMOD_FUNCTION_H

typedef struct libmod_function {
	const char *name;
	void *address;
} libmod_function_t;

typedef struct libmod_stub libmod_stub_t;

extern void *libmod_function_fromname(libmod_stub_t *stub, const char *name);

#endif // LIBMOD_FUNCTION_H
