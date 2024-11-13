{
    depfiles_gcc = "filelines.o: src/filelines.cpp src/find_most_freq.h  src/filelines_baseline.h\
",
    files = {
        "src/filelines.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-std=c++23",
            "-march=native",
            "-DNDEBUG"
        }
    }
}