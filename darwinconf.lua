

OUT_TAR = "lua.tar"
EXTRACTED_TAR_DEST = "extracted_tar"
OUT_DIR = "lua"
MAX_CONTENT = darwin.camalgamator.ONE_MB * 10
MAX_RECURSION = 100
RELEASE_DIR = "release"

ONELUA_URL = "https://raw.githubusercontent.com/lua/lua/refs/tags/5.4.7/onelua.c"
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
    darwin.dtw.remove_any(EXTRACTED_TAR_DEST)
end 

if true then return end 

print("Building Headders")
print("===================================================================")



local headers = darwin.camalgamator.generate_amalgamation("src/headers.h", MAX_CONTENT, MAX_RECURSION)

darwin.dtw.write_file(RELEASE_DIR.."/lua_hedders.h", headers)   
 
local filtrage = function(path,import)
    if import == "luac.c" then
        return "dont-change"
    end
    return  "include-once"
end

local one_lua_import =darwin.camalgamator.generate_amalgamation_with_callback(
    "src/onelua_import.c",
    filtrage,
    MAX_CONTENT,
    MAX_RECURSION
)
darwin.dtw.write_file(RELEASE_DIR.."/onelua_import.c", one_lua_import)

