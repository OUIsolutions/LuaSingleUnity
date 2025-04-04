#if defined(LUA_SINGLE_UNITY_HIDE_MAIN)
#define main LUA_SINGLE_UNITY_MAIN
#endif

#if defined(LUA_SINGLE_UNITY_POSIX_GUESS)
    #if defined(__unix__) || defined(__APPLE__) || defined(__linux__)
        #define LUA_USE_POSIX
    #endif 
#endif 

#include "../lua/onelua.c"
#if defined(LUA_SINGLE_UNITY_IMPLEMENT_MATH)
#include "math.c"
#endif 

#if defined(LUA_SINGLE_UNITY_HIDE_MAIN)
#undef main
#endif
