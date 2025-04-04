

function main()
      
    local version = darwin.argv.get_flag_arg_by_index({"version", "v"}, 1)
    if version == nil then
        print("Please provide a version number.")
        return
    end

    local out_zip = "lua"..version..".zip"
    local url= "https://github.com/lua/lua/archive/refs/tags/v"..version..".zip"
    local out_dir = "lua_code"
    if not darwin.dtw.isfile(out_zip) then
        print("Downloading "..out_zip)
        os.execute("curl -L "..url.." -o "..out_zip)
    end

    if not darwin.dtw.isdir(out_dir) then
        print("Unzipping "..out_zip)
        os.execute("unzip -q "..out_zip)
    end
     
end 