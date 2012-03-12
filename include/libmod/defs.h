#ifndef LIBMOD_DEFS_H
#define LIBMOD_DEFS_H

#if defined(_WIN32)
#	define LIBMOD_WINDOWS
#elif defined(__unix__)
#	define LIBMOD_UNIX
#else
#	error "Sorry, libmod doesn't currently support this OS. Feel free to submit a patch though!"
#endif

#ifndef LIBMOD_MAXMODULES
#	define LIBMOD_MAXMODULES 2<<7
#endif

#ifndef LIBMOX_MAXEXPORTS
#	define LIBMOD_MAXEXPORTS 2<<15
#endif

#endif // LIBMOD_DEFS_H
