#ifndef LIBMOD_DEFS_H
#define LIBMOD_DEFS_H

#if !defined(LIBMOD_WINDOWS) && !defined(LIBMOD_UNIX)
#	if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
#		define LIBMOD_WINDOWS
#	elif defined(__unix__) || defined(linux) || defined(__APPLE__) || defined(__MACH__)
#		define LIBMOD_UNIX
#	else
#		error "Sorry, libmod doesn't currently support this OS. Feel free to submit a patch though!"
#	endif
#endif

#ifndef LIBMOD_MAXMODULES
#	define LIBMOD_MAXMODULES 2<<7
#endif

#ifndef LIBMOX_MAXEXPORTS
#	define LIBMOD_MAXEXPORTS 2<<15
#endif

#endif // LIBMOD_DEFS_H
