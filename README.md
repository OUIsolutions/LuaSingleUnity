# LuaSingleUnity
LuaSingleUnity is a implementation of [lua](https://www.lua.org/)  that provides Lua in a single file format for easy integration into projects. It offers two main variants of implementation files along with a header file.


## Releases
| Item | Description |
| ---- | ----------- |
|[lua_single_unity.h](https://github.com/OUIsolutions/LuaSingleUnity/releases/download/5.4.7/lua_single_unity.h)| Header file|
|[lua_single_unity_classic_onelua.c](https://github.com/OUIsolutions/LuaSingleUnity/releases/download/5.4.7/lua_single_unity_classic_onelua.c)| single Unity definitions|
|[lua_single_unity_custom_onelua.c](https://github.com/OUIsolutions/LuaSingleUnity/releases/download/5.4.7/lua_single_unity_custom_onelua.c)| exactly the same as the classic, but with some macro renamings on [onelua.c](https://github.com/lua/lua/blob/master/onelua.c)|

## Macros
| Flag | Description |
| ---- | ----------- |
|LUA_SINGLE_UNITY_GUESS_OS | guess the os, if defined, it will use the default os check [guess_os.h](/src/guess_os.h) |
|LUA_SINGLE_UNITY_EMBED_MODE | use these if you want to embed lua into your C code, otherwise will raise **redefinition of main** |
|LUA_SINGLE_UNITY_IMPLEMENT_MATH| (implements **math.h**) use these if you dont have the **-lm** available on your os  |
|LUA_SINGLE_UNITY_IMPLEMENT_LUAC | use these if you want to compile the luac (lua bytecode generator) |
|LUA_SINGLE_UNITY_MAKE_LUA| (its default if LUA_SINGLE_UNITY_EMBED_MODE and LUA_SINGLE_UNITY_IMPLEMENT_LUAC are not defined) use these if you want to compile the lua runtime|
|LUA_SINGLE_UNITY_CLASSIC_ONE_LUA_COMPATIBILITY| it is only useful on [lua_single_unity_custom_onelua.c](https://github.com/OUIsolutions/LuaSingleUnity/releases/download/5.4.7/lua_single_unity_custom_onelua.c), with these flag will emulate the classic [onelua.c](https://github.com/lua/lua/blob/master/onelua.c)|

## Key Differences
- **lua_single_unity_classic_onelua.c** and **lua_single_unity_custom_onelua.c** are essentially identical, with the latter renaming certain macros for compatibility:
  - **MAKE_LIB** to **LUA_SINGLE_UNITY_EMBED_MODE**
  - **MAKE_LUAC** to **LUA_SINGLE_UNITY_IMPLEMENT_LUAC**
  - **MAKE_LUA** to **LUA_SINGLE_UNITY_MAKE_LUA**

## Embedding Lua
### Single Compilation
For embedding Lua in single compilation, use:
```c
#define LUA_SINGLE_UNITY_EMBED_MODE
#define LUA_SINGLE_UNITY_GUESS_OS
#include "lua_single_unity_classic_onelua.c"
int main() {

    lua_State *L = luaL_newstate();
    const char *expr = "return 3 +3 + 5"; 
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

```

### Multi Compilation
For multi-compilation embedding:
```c
#include "lua_single_unity.h"
int main() {
    // Your Lua code here
}
```
Compile with:
```bash
cc -c lua_single_unity_classic_onelua.c -DLUA_SINGLE_UNITY_GUESS_OS -DLUA_SINGLE_UNITY_EMBED_MODE
cc test.c lua_single_unity_classic_onelua.o -lm
```

## Loading Native Libraries
Native libraries are included in the amalgamation. Load them using:
```c
luaL_openlibs(L);
```
**Note:** This function can be dangerous if used in low-security contexts.

## Compiling Lua Runtime
To compile the Lua runtime:
```bash
cc lua_single_unity_classic_onelua.c -DLUA_SINGLE_UNITY_GUESS_OS -lm -o lua_runtime
```

## Compiling Lua Bytecode Compiler (luac)
To compile luac:
```bash
cc lua_single_unity_classic_onelua.c -DLUA_SINGLE_UNITY_GUESS_OS -DLUA_SINGLE_UNITY_IMPLEMENT_LUAC -lm -o luac
```
Generate bytecode:
```bash
./luac -o test.luac test.lua
```
Run bytecode:
```bash
./lua_runtime test.luac
```

## Building from Scratch
**Tools Required:**
- tar
- [Darwin](https://github.com/OUIsolutions/Darwin) v0.2.1

### Default Build
```bash
darwin run_blueprint darwinconf.lua --version 5.4.7
```

### Custom Build
```bash
darwin run_blueprint darwinconf.lua --source https://www.lua.org/ftp/lua-5.4.7.tar.gz --onelua https://raw.githubusercontent.com/lua/lua/refs/heads/master/onelua.c
```

### Offline Build
Place a **lua** directory with **onelua.c** in the repo directory, then:
```bash
darwin run_blueprint darwinconf.lua
```

## Licenses
- **Lua**: MIT License - Free for any use with credit to PUC-Rio.
- **Darwin**: MIT License - Free to use with no restrictions on usage.

For more detailed licensing information, visit [Lua's official site](https://www.lua.org/license.html) or [Darwin's GitHub](https://github.com/OUIsolutions/Darwin/blob/master/LICENSE).
