#include "../include/libmod/function.h"

#include "../include/libmod/stub.h"
#include "../include/libmod/error.h"

#include <stddef.h>
#include <string.h>
#include <assert.h>

void *libmod_function_fromname(libmod_stub_t *stub, const char *name) {
	assert(stub != NULL && name != NULL);

	uint64_t i;
	for(i = 0; i < stub->exports.count; i++) {
		if(strcmp(stub->exports.functions[i].name, name) == 0)
			return stub->exports.functions[i].address;
	}

	__libmod_error_setandret(ENOSUCHFUNCTION, name);

	return NULL;
}
