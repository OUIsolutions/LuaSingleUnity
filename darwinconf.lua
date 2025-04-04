

OUT_TAR = "lua.tar"
EXTRACTED_TAR_DEST = "extracted_tar"
OUT_DIR = "lua/"
MAX_CONTENT = darwin.camalgamator.ONE_MB * 10
MAX_RECURSION = 100
RELEASE_DIR = "release"
ONE_LUA_DEST = "lua/onelua.c"
onelua_url = "https://raw.githubusercontent.com/lua/lua/refs/tags/v5.4.7/onelua.c"
source_url = "https://www.lua.org/ftp/lua-5.4.7.tar.gz"
aply_one_lua_macro_rename = true


print("Lua Single Unity Build")
print("===================================================================")



if not darwin.dtw.isfile(OUT_TAR) then
    print("Downloading "..OUT_TAR)
    os.execute("curl -L "..source_url.." -o "..OUT_TAR)
end

if not darwin.dtw.isdir(OUT_DIR) then 
    print("Extracting "..OUT_TAR)
    os.execute("mkdir -p "..EXTRACTED_TAR_DEST)
    os.execute("tar -xzf "..OUT_TAR.." -C "..EXTRACTED_TAR_DEST)
    local INCLUDE_PATH = true
    local first_dir = darwin.dtw.list_dirs(EXTRACTED_TAR_DEST,INCLUDE_PATH)[1]
    local src = first_dir.."/src"
    darwin.dtw.copy_any_overwriting(src,OUT_DIR)
    darwin.dtw.remove_any(EXTRACTED_TAR_DEST)
end 
if not darwin.dtw.isfile(ONE_LUA_DEST) then
    print("Downloading "..ONE_LUA_DEST)
    os.execute("curl -L "..onelua_url.." -o "..ONE_LUA_DEST)
    
    
    local one_lua_content= darwin.dtw.load_file(ONE_LUA_DEST)
    if aply_one_lua_macro_rename then
        one_lua_content = string.gsub(one_lua_content, "MAKE_LIB","LUA_SINGLE_UNITY_EMBED_MODE")
        one_lua_content = string.gsub(one_lua_content, "MAKE_LUAC","LUA_SINGLE_UNITY_INPLEMENT_LUAC")
        one_lua_content = string.gsub(one_lua_content, "MAKE_LUA","LUA_SINGLE_UNITY_INPLEMENT_LUA")
        darwin.dtw.write_file(ONE_LUA_DEST, one_lua_content)
    end
end 



print("Building Headders")
print("===================================================================")



local headers = darwin.camalgamator.generate_amalgamation("src/lua_single_unity.h", MAX_CONTENT, MAX_RECURSION)

darwin.dtw.write_file(RELEASE_DIR.."/lua_single_unity.h", headers)   
 


local one_lua_import =darwin.camalgamator.generate_amalgamation("src/lua_single_unity.c",MAX_CONTENT,MAX_RECURSION)

darwin.dtw.write_file(RELEASE_DIR.."/lua_single_unity.c", one_lua_import)

