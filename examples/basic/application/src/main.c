#include "../../../../include/libmod/libmod.h"

#include <stdio.h>
#include <stddef.h>

void (*say_hi)(void);
void say_bye(void);

libmod_application_t libmod_application = {
	{
		"libmod C Application",
		"An example application to demonstrate the libmod library",
		{1, 0, 0, 0},
		{1,
			{
				{ "say_bye", &say_bye }
			}
		}
	}
};

int main(int argc, char *argv[]) {
	printf("-- Application --\n");
	printf(" -   Name: \"%s\"\n", libmod_application.stub.name);
	printf(" -   Description: \"%s\"\n", libmod_application.stub.description);
	printf(" -   Version: %i.%i.%i build %i\n", libmod_application.stub.version.major, libmod_application.stub.version.minor, libmod_application.stub.version.revision, libmod_application.stub.version.build);
	printf("-- Exports --\n");
	printf(" -   %li export(s):\n", libmod_application.stub.exports.count);

	for(int i = 0; i < libmod_application.stub.exports.count; i++) {
		printf(" -   %s -> %p\n", libmod_application.stub.exports.functions[i].name, libmod_application.stub.exports.functions[i].address);
	}

	printf("-- Module --\n");

	const char *module_name = "./module.lmm";

	libmod_module_t *module = libmod_module_load(&libmod_application, module_name);

	if(module == NULL) {
		printf(" -   (Error) %s: %s.\n", libmod_error_string(libmod_error_number()), libmod_error_details());
		return libmod_exit(libmod_error_number());
	} else {
		printf(" -   Name: \"%s\"\n", module->stub.name);
		printf(" -   Description: \"%s\"\n", module->stub.description);
		printf(" -   Version: %i.%i.%i build %i\n", module->stub.version.major, libmod_application.stub.version.minor, libmod_application.stub.version.revision, libmod_application.stub.version.build);
		printf("-- Exports --\n");
		printf(" -   %li export(s):\n", module->stub.exports.count);

		for(int i = 0; i < module->stub.exports.count; i++) {
			printf(" -   %s -> %p\n", module->stub.exports.functions[i].name, libmod_application.stub.exports.functions[i].address);
		}
	}

	say_hi = libmod_function_fromname(&module->stub, "say_hi"); // Get the libmod_modtest function inside it
	if(say_hi == NULL) {
		printf(" -   (Error) %s: %s.\n", libmod_error_string(libmod_error_number()), libmod_error_details());

		libmod_module_unload(&libmod_application, module);
		return libmod_exit(libmod_error_number());
	}

	printf("-- Function test --\n");
	printf(" - say_hi(); say_bye();: ");

	say_hi();
	say_bye();

	if(libmod_module_unload(&libmod_application, module) != ENOERROR) { // Unload the module
		printf(" -   (Error) %s: %s.\n", libmod_error_string(libmod_error_number()), libmod_error_details());

		return libmod_exit(libmod_error_number());
	}

	return ENOERROR;
}

void say_bye(void) {
	printf(" the lazy dog.\n");
}
