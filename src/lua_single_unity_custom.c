

#if defined(LUA_SINGLE_UNITY_GUESS_OSS)

    #if defined(__APPLE__)
        #include <TargetConditionals.h>
        #if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
            #define LUA_USE_IOS
        #elif defined(__MACH__)
            #define LUA_USE_MACOSX
        #endif
    #elif defined(__linux__)
        #define LUA_USE_LINUX
    #elif (defined(_WIN32) || defined(_WIN64)) && !defined(_WIN32_WCE)
        #define LUA_USE_WINDOWS
    #elif defined(__unix__) || defined(__FreeBSD__) || defined(__NetBSD__)
        #define LUA_USE_POSIX
    #endif 

#endif

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

#if defined(LUA_SINGLE_UNITY_IMPLEMENT_MATH)
#include "math.c"
#endif
