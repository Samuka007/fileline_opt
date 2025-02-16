#ifndef _FILELINES_BASELINE_H
#define _FILELINES_BASELINE_H
#include <stdint.h>

void filelines_baseline(char *argv,uint32_t *total_line_num,uint32_t *line_num);
void filelines_vectorize(char *argv,uint32_t *total_line_num,uint32_t *line_num);
// void filelines_multithread(char *filepath, uint32_t *total_line_num, uint32_t *line_num, int num_threads);

#endif