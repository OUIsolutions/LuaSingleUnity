

OUT_ZIP = "lua.zip"
OUT_DIR = "lua"
MAX_CONTENT = darwin.camalgamator.ONE_MB * 10
MAX_RECURSION = 100
RELEASE_DIR = "release"

local version = darwin.argv.get_flag_arg_by_index({"version", "v"}, 1)
if version == nil then
    print("Please provide a version number.")
    return
end

print("Lua Single Unity Build")
print("===================================================================")


local url= "https://github.com/lua/lua/archive/refs/tags/v"..version..".zip"


if not darwin.dtw.isfile(OUT_ZIP) then
    print("Downloading "..OUT_ZIP)
    os.execute("curl -L "..url.." -o "..OUT_ZIP)
end

if not darwin.dtw.isdir(OUT_DIR) then
    print("Unzipping "..OUT_ZIP)
    os.execute("unzip -q "..OUT_ZIP)
    local generated_dir ="lua-"..version
    darwin.dtw.move_any_overwriting(generated_dir, OUT_DIR)
    darwin.dtw.remove_any(generated_dir)
end

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
darwin.dtw.write_file(RELEASE_DIR.."/one_lua_import.c", one_lua_import)

