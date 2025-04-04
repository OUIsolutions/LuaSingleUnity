# LuaSingleUnity
Lua Single Unity mode

# Compiling the runtime

if you want to compile the **lua_runtime**, you can compile with:

```bash
cc lua_single_unity_classic_onelua.c -DLUA_SINGLE_UNITY_GUESS_OSS -lm -o lua_runtime
```

## Compiling luac (lua bytecode compiler)
if you want to compile the **luac**, you can compile with:

```bash
cc lua_single_unity_classic_onelua.c -DLUA_SINGLE_UNITY_GUESS_OSS -DLUA_SINGLE_UNITY_INPLEMENT_LUAC -lm -o luac
```
than you can generate your bytecodes with
```bash
./luac -o test.luac test.lua
```
and running the bytecode in the lua virtual machine with
```bash
./lua_runtime test.luac
```

## Embeding lua




# Build From Scracth

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
