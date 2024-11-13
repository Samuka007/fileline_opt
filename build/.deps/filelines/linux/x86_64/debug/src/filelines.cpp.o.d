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
    depfiles_gcc = "filelines.o: src/filelines.cpp src/find_most_freq.h  src/filelines_baseline.h\
",
    files = {
        "src/filelines.cpp"
    }
}