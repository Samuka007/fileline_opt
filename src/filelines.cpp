/*
The MIT License (MIT)

Copyright (C) 2022, chenhu@scut.edu.cn

Permission is hereby granted, free of charge, 
to any person obtaining a copy of this software 
and associated documentation files (the "Software"), 
to deal in the Software without restriction, i
ncluding without limitation the rights to use, copy, 
modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit 
persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice 
shall be included in all copies or substantial portions 
of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF 
ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED 
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR 
A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT 
SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR 
ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN 
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "find_most_freq.h"
#include "filelines_baseline.h"

uint32_t line_num[MAX_LEN];
uint32_t total_line_num;
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s filepath", argv[0]);
        return -1;
    }

    // for (int i = 0; i < MAX_LEN; i++) line_num[i] = 0;
    // total_line_num = 0;

    // auto start = std::chrono::high_resolution_clock::now();
    // filelines_baseline(argv[1], &total_line_num, line_num);
    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> elapsed = end - start;
    // printf("Baseline execution time: %f seconds\n", elapsed.count());

    uint32_t most_freq_len, most_freq_len_linenum;
    // find_most_freq_line(line_num, &most_freq_len, &most_freq_len_linenum);
    // printf("%d %d %d\n", total_line_num, most_freq_len, most_freq_len_linenum);

    // for (int i = 0; i < MAX_LEN; i++) line_num[i] = 0;
    // total_line_num = 0;

    // start = std::chrono::high_resolution_clock::now();
    filelines_vectorize(argv[1], &total_line_num, line_num);
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // printf("Vectorized execution time: %f seconds\n", elapsed.count());

    find_most_freq_line(line_num, &most_freq_len, &most_freq_len_linenum);
    printf("%d %d %d\n", total_line_num, most_freq_len, most_freq_len_linenum);

    // for (int i = 0; i < MAX_LEN; i++) line_num[i] = 0;
    // total_line_num = 0;

    // int num_threads = std::thread::hardware_concurrency();
    // start = std::chrono::high_resolution_clock::now();
    // filelines_multithread(argv[1], &total_line_num, line_num, num_threads);
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // printf("Multithreaded execution time: %f seconds\n", elapsed.count());

    // find_most_freq_line(line_num, &most_freq_len, &most_freq_len_linenum);
    // printf("%d %d %d\n", total_line_num, most_freq_len, most_freq_len_linenum);

    return 0;
}
