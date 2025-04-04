# LuaSingleUnity
Lua Single Unity mode


# Build From Scracth

if you want to build from scratch, you will need to have the follwoing tools 
installed 

- tar (if not provide the source)
- [darwin](https://github.com/OUIsolutions/Darwin) on version **0.2.1**

### Default Build
for build using [onelua.c](https://github.com/lua/lua/blob/master/onelua.c) and 
[lua_source](https://www.lua.org/versions.html) you can run 

```bash
darwin run_blueprint darwinconf.lua --version 5.4.7
```
this will create a folder called **release** and inside it you will find the
output


### Build passing font 
if you have your fonts, you can pass in these way
```bash
