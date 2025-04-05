#include "guess_os.h"
#include "../lua/lprefix.h"

/* setup for luaconf.h */
#define LUA_CORE
#define LUA_LIB
#define ltable_c
#define lvm_c



#include "../lua/lua.h"
#include "../lua/lualib.h"
#include "../lua/lauxlib.h"