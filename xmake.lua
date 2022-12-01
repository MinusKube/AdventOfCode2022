if is_mode("debug") then
   set_symbols("debug")
   set_optimize("none")
end

target("advent_of_code_2022")
    set_kind("binary")
    add_files("src/*.cpp")
    set_targetdir("build")