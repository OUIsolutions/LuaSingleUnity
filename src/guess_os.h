
#if defined(LUA_SINGLE_UNITY_GUESS_OS)

    #if defined(__APPLE__)
        #include <TargetConditionals.h>
        #if TARGET_OS_MAC && !TARGET_OS_IPHONE
            #define LUA_USE_MACOSX
        #elif TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
            #define LUA_USE_IOS
        #endif
    #elif defined(__linux__)
        #define LUA_USE_LINUX
    #elif (defined(_WIN32) || defined(_WIN64)) && !defined(_WIN32_WCE)
        #define LUA_USE_WINDOWS
    #elif defined(__unix__) || defined(__FreeBSD__) || defined(__NetBSD__)
        #define LUA_USE_POSIX
    #endif

#endif