
#include "guess_os.h"

#if defined(LUA_SINGLE_UNITY_ONE_LUA_COMPATIBILITY)
    #if defined(MAKE_LIB)
        #define LUA_SINGLE_UNITY_EMBED_MODE 
    #endif 
    #if defined(MAKE_LUAC)
        #define LUA_SINGLE_UNITY_INPLEMENT_LUAC
    #endif
    #if defined(MAKE_LUA)
        #define LUA_SINGLE_UNITY_MAKE_LUA
    #endif 
#endif
#include "../lua/onelua_custom.c"
#include "math.c"
