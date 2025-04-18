

local LUA_TAR = "lua.tar"
local EXTRACTED_TAR_DEST = "extracted_tar"
local LUA_DIR = "lua/"
local ONE_LUA_LOCATION = LUA_DIR.."onelua.c"
local MAX_CONTENT = darwin.camalgamator.ONE_MB * 10
local MAX_RECURSION = 100
local RELEASE_DIR = "release"
local CUSTON_ONE_LUA_DEST = "lua/onelua_custom.c"
local one_lua_exist = darwin.dtw.isfile(ONE_LUA_LOCATION)
local lua_dir_exist = darwin.dtw.isdir(LUA_DIR)

local onelua_font = darwin.argv.get_flag_arg_by_index({ "onelua" ,"o"}, 1)
local source_font = darwin.argv.get_flag_arg_by_index({ "source" ,"s"}, 1)


local version = nil
local version_is_required = true

if  onelua_font and  source_font then 
    version_is_required = false
end

if  one_lua_exist and  lua_dir_exist then 
    version_is_required = false
end

if  version_is_required then
    version =darwin.argv.get_flag_arg_by_index({ "version" ,"v"}, 1)
    if not version then
        print("Please provide the version of Lua you want to download. (--version) or (-- onelua <font> --source <font>)")
        return 
    end
    if not onelua_font then 
        onelua_font = "https://raw.githubusercontent.com/lua/lua/refs/tags/v"..version.."/onelua.c"
    end 
    if not source_font then 
        source_font = "https://www.lua.org/ftp/lua-"..version..".tar.gz"
    end 
    
end 






print("Lua Single Unity Build")
print("========================Getting Headders======================================")

if not lua_dir_exist then 
    print("Downloading "..LUA_TAR)
    os.execute("curl -L "..source_font.." -o "..LUA_TAR)
    print("Extracting "..LUA_TAR)
    os.execute("mkdir -p "..EXTRACTED_TAR_DEST)
    os.execute("tar -xzf "..LUA_TAR.." -C "..EXTRACTED_TAR_DEST)
    local INCLUDE_PATH = true
    local first_dir = darwin.dtw.list_dirs(EXTRACTED_TAR_DEST,INCLUDE_PATH)[1]
    local src = first_dir.."/src"
    darwin.dtw.copy_any_overwriting(src,LUA_DIR)
    --darwin.dtw.remove_any(EXTRACTED_TAR_DEST)
end 

if not one_lua_exist then
    print("Downloading onelua.c")
    os.execute("curl -L "..onelua_font.." -o "..ONE_LUA_LOCATION)

end 




one_lua_content= darwin.dtw.load_file(ONE_LUA_LOCATION)
print("Renaming macros in "..CUSTON_ONE_LUA_DEST)
one_lua_content = string.gsub(one_lua_content, "MAKE_LIB","LUA_SINGLE_UNITY_EMBED_MODE")
one_lua_content = string.gsub(one_lua_content, "MAKE_LUAC","LUA_SINGLE_UNITY_INPLEMENT_LUAC")
one_lua_content = string.gsub(one_lua_content, "MAKE_LUA","LUA_SINGLE_UNITY_INPLEMENT_LUA_RUNTIME")
darwin.dtw.write_file(CUSTON_ONE_LUA_DEST,one_lua_content)


print("==========================Building Headders===================================")



local headers = darwin.camalgamator.generate_amalgamation("src/lua_single_unity.h", MAX_CONTENT, MAX_RECURSION)

darwin.dtw.write_file(RELEASE_DIR.."/lua_single_unity.h", headers)   
 

print("==========================Building Sources====================================")

local custom_one_lua_import =darwin.camalgamator.generate_amalgamation("src/lua_single_unity_custom_onelua.c",MAX_CONTENT,MAX_RECURSION)

darwin.dtw.write_file(RELEASE_DIR.."/lua_single_unity_custom_onelua.c", custom_one_lua_import)

local classic_one_lua_import =darwin.camalgamator.generate_amalgamation("src/lua_single_unity_classic_onelua.c",MAX_CONTENT,MAX_RECURSION)
darwin.dtw.write_file(RELEASE_DIR.."/lua_single_unity_classic_onelua.c", classic_one_lua_import)
