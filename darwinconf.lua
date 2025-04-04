

OUT_TAR = "lua.tar"
EXTRACTED_TAR_DEST = "extracted_tar"
OUT_DIR = "lua/"
MAX_CONTENT = darwin.camalgamator.ONE_MB * 10
MAX_RECURSION = 100
RELEASE_DIR = "release"
ONE_LUA_DEST = "lua/onelua.c"
SOURCE_URL = "https://www.lua.org/ftp/lua-5.4.7.tar.gz"



print("Lua Single Unity Build")
print("===================================================================")



if not darwin.dtw.isfile(OUT_TAR) then
    print("Downloading "..OUT_TAR)
    os.execute("curl -L "..SOURCE_URL.." -o "..OUT_TAR)

 
end
if not darwin.dtw.isdir(OUT_DIR) then 
    print("Extracting "..OUT_TAR)
    os.execute("mkdir -p "..EXTRACTED_TAR_DEST)
    os.execute("tar -xzf "..OUT_TAR.." -C "..EXTRACTED_TAR_DEST)
    local INCLUDE_PATH = true
    local first_dir = darwin.dtw.list_dirs(EXTRACTED_TAR_DEST,INCLUDE_PATH)[1]
    local src = first_dir.."/src"
    darwin.dtw.copy_any_overwriting(src,OUT_DIR)
   -- darwin.dtw.remove_any(EXTRACTED_TAR_DEST)
end 




print("Building Headders")
print("===================================================================")



local headers = darwin.camalgamator.generate_amalgamation("src/lua_single_unity.h", MAX_CONTENT, MAX_RECURSION)

darwin.dtw.write_file(RELEASE_DIR.."/lua_single_unity.h", headers)   
 


local one_lua_import =darwin.camalgamator.generate_amalgamation("src/lua_single_unity.c",MAX_CONTENT,MAX_RECURSION)

darwin.dtw.write_file(RELEASE_DIR.."/lua_single_unity.c", one_lua_import)

