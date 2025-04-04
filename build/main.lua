

function main()

      
    local out_zip = "lua-"..VERSION..".zip"
    local url= "https://github.com/lua/lua/archive/refs/tags/v5.4.7.ziphttps://github.com/lua/lua/archive/refs/tags/"..VERSION..".zip"
    if not darwin.dtw.is_file(out_zip) then
        print("Downloading "..out_zip)
        os.execute("curl -L "..url.." -o "..out_zip)
    end
    
     
end 