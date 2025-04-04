#ifdef LUA_SINGLE_UNITY_HIDE_MAIN
#define main LUA_SINGLE_UNITY_MAIN
#endif
#include "../lua/onelua.c"

#ifdef LUA_SINGLE_UNITY_HIDE_MAIN
#undef main
#endif
