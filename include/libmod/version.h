#ifndef LIBMOD_VERSION_H
#define LIBMOD_VERSION_H

typedef struct libmod_version {
	const unsigned int major;
	const unsigned int minor;
	const unsigned int revision;
	const unsigned int build;
} libmod_version_t;

#endif /* LIBMOD_VERSION_H */
