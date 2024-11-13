{
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-g",
            "-O0",
            "-std=c++23",
            "-march=native",
            "-mavx512f"
        }
    },
    depfiles_gcc = "find_most_freq.o: src/find_most_freq.cpp src/find_most_freq.h\
",
    files = {
        "src/find_most_freq.cpp"
    }
}