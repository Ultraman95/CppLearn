set_project("Base")

-- add modes: debug and release 
add_rules("mode.debug", "mode.release")
set_languages("cxx11")

add_requires("vcpkg::gtest","vcpkg::cli11")

-- lua语言测试
function testLua()
	print("TestLua")
end

-- add_defines("")

-- add target
target("Base")

	--testLua()
    -- set kind
    set_kind("binary")
	
    add_headerfiles("src/**/*.h")

	add_includedirs("src/basetest/")
	add_includedirs("src/datastruct/")
	add_includedirs("src/memdatabase/")
	add_includedirs("src/platform/")
	add_includedirs("src/utils/")
	add_includedirs("src/utils/cli/")
	add_includedirs("src/utils/parser/")
	if is_os("linux") then
		add_includedirs("src/utils/redis/")
	end
	
    -- add files
	add_files("src/basetest/*.cpp")
    add_files("src/datastruct/*.cpp")
	add_files("src/memdatabase/*.cpp")
	add_files("src/utils/*.cpp")
	add_files("src/utils/cli/*.cpp")
	if is_os("linux") then
		add_files("src/utils/redis/*.cpp")
	end

	add_files("src/main.cpp")
	

	if is_os("windows") then
		add_linkdirs("./libs/win")
	elseif is_os("linux") then
		add_linkdirs("./libs/linux")
		add_links("hiredis")
		add_links("pthread")	--gtest需要用到pthread
	end
	add_packages("vcpkg::gtest","vcpkg::cli11")

	--xmake run时，自动加载所需dll动态库
    before_run(function (target)
        os.addenv("PATH", "./dlls")
    end)






--
-- FAQ
--
-- You can enter the project directory firstly before building project.
--   
--   $ cd projectdir
-- 
-- 1. How to build project?
--   
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install 
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code 
--    -- add macro defination
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "cxx11")
--
--    -- set optimization: none, faster, fastest, smallest 
--    set_optimize("fastest")
--    
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox", "z", "pthread")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--
-- 7. If you want to known more usage about xmake, please see http://xmake.io/#/home
--
    
