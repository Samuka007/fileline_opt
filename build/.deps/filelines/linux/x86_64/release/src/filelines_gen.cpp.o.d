{
    depfiles_gcc = "filelines_gen.o: src/filelines_gen.cpp src/find_most_freq.h\
",
    files = {
        "src/filelines_gen.cpp"
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