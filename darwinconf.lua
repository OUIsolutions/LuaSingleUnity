

function main()
      
    local out_zip = "lua"..VERSION..".zip"
    local url= "https://github.com/lua/lua/archive/refs/tags/v"..VERSION..".zip"
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