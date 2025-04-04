## LuaSingleUnity
Lua Single Unity mode

### Releases
| Item | Description |
| ---- | ----------- |
|[lua_single_unity.h](https://github.com/OUIsolutions/LuaSingleUnity/releases/download/5.4.7/lua_single_unity.h)| Header file|
|[lua_single_unity_classic_onelua.c](https://github.com/OUIsolutions/LuaSingleUnity/releases/download/5.4.7/lua_single_unity_classic_onelua.c)| single Unity definitions|
|[lua_single_unity_custom_onelua.c](https://github.com/OUIsolutions/LuaSingleUnity/releases/download/5.4.7/lua_single_unity_custom_onelua.c)| exactly the same as the classic, but with some macro renamings on [onelua.c](https://github.com/lua/lua/blob/master/onelua.c)|

### Macros
| Flag | Description |
| ---- | ----------- |
|LUA_SINGLE_UNITY_GUESS_OS | guess the os, if defined, it will use the default os check [guess_os.h](/src/guess_os.h) |
|LUA_SINGLE_UNITY_EMBED_MODE | use these if you want to embed lua into your C code , otherwise will raise **redefinition of main** |
|LUA_SINGLE_UNITY_IMPLEMENT_MATH| (implements **math.h**) use these if you dont have the **-lm** available on your os  |
|LUA_SINGLE_UNITY_IMPLEMENT_LUAC | use these if you want to compile the luac (lua bytecode generator) |
|LUA_SINGLE_UNITY_MAKE_LUA| (its default if LUA_SINGLE_UNITY_EMBED_MODE and LUA_SINGLE_UNITY_IMPLEMENT_LUAC are not defined) use these if you want to compile the lua runtime|
|LUA_SINGLE_UNITY_CLASSIC_ONE_LUA_COMPATIBILITY| it is only useful on [lua_single_unity_custom_onelua.c](https://github.com/OUIsolutions/LuaSingleUnity/releases/download/5.4.7/lua_single_unity_custom_onelua.c), with these flag will emulate the classic [onelua.c](https://github.com/lua/lua/blob/master/onelua.c)|

### Main difference between [lua_single_unity_classic_onelua.c](https://github.com/OUIsolutions/LuaSingleUnity/releases/download/5.4.7/lua_single_unity_classic_onelua.c) and [lua_single_unity_custom_onelua.c](https://github.com/OUIsolutions/LuaSingleUnity/releases/download/5.4.7/lua_single_unity_custom_onelua.c)
basically they are the same, the main difference is that these following macros are renamed

| Old Name | New Name |
| -------- | -------- |
|MAKE_LIB  | LUA_SINGLE_UNITY_EMBED_MODE |
|MAKE_LUAC | LUA_SINGLE_UNITY_IMPLEMENT_LUAC |
|MAKE_LUA | LUA_SINGLE_UNITY_MAKE_LUA |


### Embedding Lua in Single Unity Compilation
if you want to embed lua in single compilation, create a **test.c** file:

```c
#define LUA_SINGLE_UNITY_EMBED_MODE
#define LUA_SINGLE_UNITY_GUESS_OS
#include "lua_single_unity_classic_onelua.c"
int main() {

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    const char *expr = "return os.execute('echo careful these could be executed by your user ')"; 
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

### Embedding lua in Multi Compilation
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

### Loading Native libs
native libs are contained into the amalgamation, so you can just call the **luaL_openlibs(L);**
function to load the native libs.
Note that, this is a dangerous function, since if you are inside a low code, it can allow
users to run any code, so be careful with this function.
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


## Compiling the runtime
if you want to compile the **lua_runtime**, you can compile with:

```bash
cc lua_single_unity_classic_onelua.c -DLUA_SINGLE_UNITY_GUESS_OS -lm -o lua_runtime
```

### Compiling luac (lua bytecode compiler)
if you want to compile the **luac**, you can compile with:

```bash
cc lua_single_unity_classic_onelua.c -DLUA_SINGLE_UNITY_GUESS_OS -DLUA_SINGLE_UNITY_IMPLEMENT_LUAC -lm -o luac
```
then you can generate your bytecodes with
```bash
./luac -o test.luac test.lua
```
and running the bytecode in the lua virtual machine with
```bash
./lua_runtime test.luac
```




## Build From Scratch

if you want to build from scratch, you will need to have the following tools 
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
if you have your fonts, you can pass in this way
```bash
 darwin run_blueprint darwinconf.lua --source https://www.lua.org/ftp/lua-5.4.7.tar.gz --onelua https://raw.githubusercontent.com/lua/lua/refs/heads/master/onelua.c
```

### Build offline
also ,you can put a dir called **lua** at the same dir of the repo, and call:
(note that you also must provide the lua/onelua.c file)
```bash
darwin run_blueprint darwinconf.lua
```

### Licenses and Attributions


## [Lua](https://www.lua.org/) and [lua Github](https://github.com/lua/lua)

Lua is free software distributed under the terms of the MIT license reproduced here. Lua may be used for any purpose, including commercial purposes, at absolutely no cost. No paperwork, no royalties, no GNU-like "copyleft" restrictions, either. Just download it and use it.

Lua is certified Open Source software. [Open Source Initiative Approved License]Its license is simple and liberal and is compatible with GPL. Lua is not in the public domain and PUC-Rio keeps its copyright.

The spirit of the Lua license is that you are free to use Lua for any purpose at no cost without having to ask us. The only requirement is that if you do use Lua, then you should give us credit by including the copyright notice somewhere in your product or its documentation. A nice, but optional, way to give us further credit is to include a Lua logo and a link to our site in a web page for your product.

The Lua language is entirely designed, implemented, and maintained by a team at PUC-Rio in Brazil. The implementation is not derived from licensed software.


## [Darwin](https://github.com/OUIsolutions/Darwin/)
MIT License

Copyright (c) 2024 OUI

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
