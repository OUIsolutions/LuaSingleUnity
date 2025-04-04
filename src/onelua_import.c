


#if defined(LUA_SINGLE_UNITY_HIDE_MAIN)
    //these its in case some one were crazy enough to define a main for what ever reason
    #ifdef main 
        #define LUA_SINGLE_UNITY_PREV_MAIN main
        #undef main
    #endif

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

#if defined(LUA_SINGLE_UNITY_HIDE_MAIN) && defined(LUA_SINGLE_UNITY_PREV_MAIN)
    #ifdef LUA_SINGLE_UNITY_PREV_MAIN
        #define main LUA_SINGLE_UNITY_PREV_MAIN
    #endif
#endif 

#if defined(LUA_SINGLE_UNITY_HIDE_MAIN) && !defined(LUA_SINGLE_UNITY_PREV_MAIN)
    #undef main
#endif 

