#define LUA_SINGLE_UNITY_EMBED_MODE
#define LUA_SINGLE_UNITY_GUESS_OS
#include "lua_single_unity_classic_onelua.c"

int main() {

    lua_State *L = luaL_newstate();
    const char *expr = "return 1 + 2 * 3"; 
    if (luaL_dostring(L, expr) == LUA_OK) {
        if (lua_isnumber(L, -1)) { 
            double result = lua_tonumber(L, -1);
            printf("result: %f\n", result);
        }
    } else {
        printf("Error: %s\n", lua_tostring(L, -1)); 
    }
    lua_close(L); 
    return 0;
}