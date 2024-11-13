{
    files = {
        "src/filelines_baseline.cpp"
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
            "-mavx512f",
            "-DNDEBUG"
        }
    },
    depfiles_gcc = "filelines_baseline.o: src/filelines_baseline.cpp src/filelines_baseline.h  src/find_most_freq.h\
"
}