



#if defined(LUA_SINGLE_UNITY_GUESS_OSS)


    #if defined(__linux__)
        #define LUA_USE_LINUX
    #elif defined(_WIN32) || defined(_WIN64) && !defined(_WIN32_WCE)
        #define LUA_USE_WINDOWS
    #elif defined(__MACH__)
        #define LUA_USE_MACOSX      
    #elif defined(__unix__) || defined(__APPLE__) 
        #define LUA_USE_POSIX
    #endif 



#endif 

#include "../lua/onelua.c"
#if defined(LUA_SINGLE_UNITY_IMPLEMENT_MATH)
#include "math.c"
#endif 



