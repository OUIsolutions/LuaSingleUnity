

OUT_ZIP = "lua.zip"
OUT_DIR = "lua"


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
    
