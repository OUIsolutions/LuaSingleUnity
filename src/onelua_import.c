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

#include "../lua/onelua.c"
#if defined(LUA_SINGLE_UNITY_IMPLEMENT_MATH)
#include "math.c"
#endif