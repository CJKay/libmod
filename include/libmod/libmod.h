#ifndef LIBMOD_H
#define LIBMOD_H

#include "defs.h"
#include "error.h"
#include "version.h"
#include "function.h"
#include "exports.h"
#include "stub.h"
#include "module.h"
#include "modules.h"
#include "application.h"

#if defined(LIBMOD_WINDOWS)
#include <windows.h>
#endif

extern int libmod_exit(int code);
extern char *libmod_strdup(const char *src);

#endif //LIBMOD_H
