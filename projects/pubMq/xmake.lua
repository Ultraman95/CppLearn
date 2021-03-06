set_project("pubMq")

-- add modes: debug and release 
add_rules("mode.debug", "mode.release")

add_defines("WIN32")

add_requires("vcpkg::paho-mqtt","vcpkg::pthreads")

-- add target
target("pubMq")
    -- set kind
    set_kind("binary")

    -- add files
    add_files("src/*.c") 
	
	add_packages("vcpkg::paho-mqtt","vcpkg::pthreads")
	
	
	--如果没有将vcpkg/installed的bin加入环境变量，则需要使用下面语句动态加入
	--add_runenvs("PATH", "E:/Program Files/vcpkg/installed/x64-windows/bin", "E:/Program Files/vcpkg/installed/x86-windows/bin")
	
	
	
	--xmake run,发现dll,但是vs不支持
	--before_run(function (target)
        --os.addenv("PATH", "E:/Program Files/vcpkg/installed/x64-windows/bin")
		--os.addenv("PATH", "E:/Program Files/vcpkg/installed/x86-windows/bin")
    --end)

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
    
