#define LUA_SINGLE_UNITY_EMBED_MODE
#define LUA_SINGLE_UNITY_GUESS_OS
#include "lua_single_unity_classic_onelua.c"
int main() {

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    const char *expr = "return os.execute('echo carefull these could be executed by your user ')"; 
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