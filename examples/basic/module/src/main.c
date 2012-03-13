#include "../../../../include/libmod/libmod.h"

#include <stdio.h>
#include <stddef.h>

void (*say_bye)(void);
void say_hi(void);

libmod_module_t libmod_module = {
	{
		"libmod C Module",
		"An example module to demonstrate the libmod library",
		{1, 0, 0, 0},
		{1,
			{
				{ "say_hi", &say_hi }
			}
		}
	}
};

void say_hi(void) {
	printf("The quick brown fox jumped over");
}
