
#include "guess_os.h"

#if defined(LUA_SINGLE_UNITY_EMBED_MODE)
    #define MAKE_LIB
#endif 

#if defined(LUA_SINGLE_UNITY_INPLEMENT_LUAC)
    #define MAKE_LUAC
#endif

#if defined(LUA_SINGLE_UNITY_MAKE_LUA)
    #define MAKE_LUA
#endif

#include "../lua/onelua.c"
#include "math.c"
