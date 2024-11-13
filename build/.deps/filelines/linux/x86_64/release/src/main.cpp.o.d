{
    depfiles_gcc = "main.o: src/main.cpp src/find_most_freq.h src/filelines_baseline.h\
",
    files = {
        "src/main.cpp"
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
            "-fopt-info-vec-missed",
            "-fopt-info-vec",
            "-DNDEBUG"
        }
    }
}