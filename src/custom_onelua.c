



#ifndef LUA_SINGLE_UNITY_MAKE_LIB
#ifndef LUA_SINGLE_UNITY_MAKE_LUAC
#ifndef LUA_SINGLE_UNITY_MAKE_LUA
#define LUA_SINGLE_UNITY_MAKE_LUA
#endif
#endif
#endif


/*
** Choose suitable platform-specific features. Default is no
** platform-specific features. Some of these options may need extra
** libraries such as -ldl -lreadline -lncurses
*/
#if 0
#define LUA_USE_LINUX
#define LUA_USE_MACOSX
#define LUA_USE_POSIX
#define LUA_ANSI
#endif


/* no need to change anything below this line ----------------------------- */

#include "../lua/lprefix.h"

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/* setup for luaconf.h */
#define LUA_CORE
#define LUA_LIB
#define ltable_c
#define lvm_c
#include "../lua/luaconf.h"

/* do not export internal symbols */
#undef LUAI_FUNC
#undef LUAI_DDEC
#undef LUAI_DDEF
#define LUAI_FUNC	static
#define LUAI_DDEC(def)	/* empty */
#define LUAI_DDEF	static

/* core -- used by all */
#include "../lua/lzio.c"
#include "../lua/lctype.c"
#include "../lua/lopcodes.c"
#include "../lua/lmem.c"
#include "../lua/lundump.c"
#include "../lua/ldump.c"
#include "../lua/lstate.c"
#include "../lua/lgc.c"
#include "../lua/llex.c"
#include "../lua/lcode.c"
#include "../lua/lparser.c"
#include "../lua/ldebug.c"
#include "../lua/lfunc.c"
#include "../lua/lobject.c"
#include "../lua/ltm.c"
#include "../lua/lstring.c"
#include "../lua/ltable.c"
#include "../lua/ldo.c"
#include "../lua/lvm.c"
#include "../lua/lapi.c"

/* auxiliary library -- used by all */
#include "../lua/lauxlib.c"

/* standard library  -- not used by luac */
#ifndef LUA_SINGLE_UNITY_MAKE_LUAC
#include "../lua/lbaselib.c"
#include "../lua/lcorolib.c"
#include "../lua/ldblib.c"
#include "../lua/liolib.c"
#include "../lua/lmathlib.c"
#include "../lua/loadlib.c"
#include "../lua/loslib.c"
#include "../lua/lstrlib.c"
#include "../lua/ltablib.c"
#include "../lua/lutf8lib.c"
#include "../lua/linit.c"
#endif

/* lua */
#ifdef LUA_SINGLE_UNITY_MAKE_LUA
#include "../lua/lua.c"
#endif

/* luac */
#ifdef LUA_SINGLE_UNITY_MAKE_LUAC
#include "../lua/luac.c"
#endif
