#if defined(LUA_SINGLE_UNITY_HIDE_MAIN)
#define main LUA_SINGLE_UNITY_MAIN
#endif


#include "../lua/onelua.c"
#if defined(LUA_SINGLE_UNITY_IMPLEMENT_MATH)
#include "math.c"
#endif 

#if defined(LUA_SINGLE_UNITY_HIDE_MAIN)
#undef main
#endif
