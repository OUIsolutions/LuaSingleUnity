# LuaSingleUnity
Lua Single Unity mode

## Releases
| Item | Description |
| ---- | ----------- |
|[lua_single_unity.h](https://github.com/OUIsolutions/LuaSingleUnity/releases/download/5.4.7/lua_single_unity.h)| Header file|
|[lua_single_unity_classic_onelua.c](https://github.com/OUIsolutions/LuaSingleUnity/releases/download/5.4.7/lua_single_unity_classic_onelua.c)| single Unity definitions|
|[lua_single_unity_custom_onelua.c](https://github.com/OUIsolutions/LuaSingleUnity/releases/download/5.4.7/lua_single_unity_custom_onelua.c)| exactly the same as the classic, but with some customization on [onelua.c](https://github.com/lua/lua/blob/master/onelua.c)|

## Flags
| Flag | Description |
| ---- | ----------- |
|LUA_SINGLE_UNITY_GUESS_OS | guess the os, if not defined, it will use the default os check [guess_os.h](/src/guess_os.h) |
|LUA_SINGLE_UNITY_EMBED_MODE | use these if you want to embed lua into your C code , otherwise will raises **redefinition of main** |
|LUA_SINGLE_UNITY_INPLEMENT_LUAC | use these if you want to compile the luac (lua bytecode generator) |
|LUA_SINGLE_UNITY_MAKE_LUA| (its default if LUA_SINGLE_UNITY_EMBED_MODE and LUA_SINGLE_UNITY_INPLEMENT_LUAC are not defined) use these if you want to compile the lua runtime|
|LUA_SINGLE_UNITY_CLASSIC_ONE_LUA_COMPATIBILITY| it is only usefull on [lua_single_unity_custom_onelua.c](https://github.com/OUIsolutions/LuaSingleUnity/releases/download/5.4.7/lua_single_unity_custom_onelua.c) with these flag will emulate the classic [onelua.c](https://github.com/lua/lua/blob/master/onelua.c)|

## Embeding Lua in Single Unity Compilation
if you want to embed lua in single compilation, create a **test.c** file:

```c
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

```

## Embeding lua in Multi Compilation
if you want to embed lua in multi compilation, create a **test.c** file:

```c
#include "lua_single_unity.h"

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
```
and compile with:

```bash
 cc -c lua_single_unity_classic_onelua.c -DLUA_SINGLE_UNITY_GUESS_OS -DLUA_SINGLE_UNITY_EMBED_MODE
cc  test.c lua_single_unity_classic_onelua.o -lm
```

## Loading Native libs
native libs are contained into the amalgamation, so you can just call the **luaL_openlibs(L);**
function to load the native libs.
Note that, these its a dangerous function, since if you are inside a a low code, it can allow
users to run any code, so be careful with this function.
```



## Compiling the runtime
if you want to compile the **lua_runtime**, you can compile with:

```bash
cc lua_single_unity_classic_onelua.c -DLUA_SINGLE_UNITY_GUESS_OS -lm -o lua_runtime
```

## Compiling luac (lua bytecode compiler)
if you want to compile the **luac**, you can compile with:

```bash
cc lua_single_unity_classic_onelua.c -DLUA_SINGLE_UNITY_GUESS_OS -DLUA_SINGLE_UNITY_INPLEMENT_LUAC -lm -o luac
```
than you can generate your bytecodes with
```bash
./luac -o test.luac test.lua
```
and running the bytecode in the lua virtual machine with
```bash
./lua_runtime test.luac
```





## Build From Scracth

if you want to build from scratch, you will need to have the follwoing tools 
installed 

- tar (if not provide the **lua** dir)
- [darwin](https://github.com/OUIsolutions/Darwin) on version **0.2.1**

### Default Build
for build using [onelua.c](https://github.com/lua/lua/blob/master/onelua.c) and 
[lua_source](https://www.lua.org/versions.html) you can run 

```bash
darwin run_blueprint darwinconf.lua --version 5.4.7
```
this will create a folder called **release** and inside it you will find the
output


### Build passing font url
if you have your fonts, you can pass in these way
```bash
 darwin run_blueprint darwinconf.lua --source https://www.lua.org/ftp/lua-5.4.7.tar.gz --onelua https://raw.githubusercontent.com/lua/lua/refs/heads/master/onelua.c
```

### Build offline
also ,you can put a dir called **lua** at the same dir of the repo, and call:
(note that you also must provide the lua/onelua.c file)
```bash
darwin run_blueprint darwinconf.lua
```
