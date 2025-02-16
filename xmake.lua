add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})


set_toolchains("gcc")
target("filelines")
    set_kind("binary")
    add_files("src/*.cpp")
    set_targetdir("bin")
    set_filename("fileline")

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
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
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
   -- add_defines("EXPAND")
   set_policy("build.warning", true)
   set_languages("c23", "c++23")
   -- add_cxflags("-march=native")
   -- add_cxxflags("/Qpar")
   -- add_cxxflags("/Qpar-report:2")
   -- add_cxxflags("/Qvec-report:2")
   -- add_cxxflags("/arch:SSE4")

   -- add_cxxflags("-funroll-loops")
   -- add_cxxflags("-msse4.2")
   add_cxxflags("-march=native -mavx512f")
   -- add_cxxflags("-fopt-info-vec-missed")
   -- add_cxxflags("-fopt-info-vec")
   --add_cxxflags("-Rpass=loop-vectorize", {force = true})
   --add_cxxflags("-Rpass-missed=loop-vectorize", {force = true})
   --add_cxxflags("-Rpass-analysis=loop-vectorize", {force = true})
--
--    -- set optimization: none, faster, fastest, smallest
   set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--

-- @endcode
--

-- 设置调试模式
if is_mode("debug") then
    set_symbols("debug")
    set_optimize("none")
end

-- 设置默认运行时参数
on_run(function (target)
    if is_mode("debug") then
        os.execv(target:targetfile(), {"data_small"})
    else
        os.execv(target:targetfile(), {"data_small"})
    end
end)


