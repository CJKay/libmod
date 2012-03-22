#ifndef LIBMOD_VERSION_H
#define LIBMOD_VERSION_H

#include <stdint.h>

typedef struct libmod_version {
	uint16_t major;
	uint16_t minor;
	uint16_t revision;
	uint16_t build;
} libmod_version_t;

#endif /* LIBMOD_VERSION_H */
