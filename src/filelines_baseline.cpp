#include "filelines_baseline.h"
#include "find_most_freq.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
// #include<iostream>
// #include <thread>
// #include <vector>

#define BLOCK_SIZE 256 * 1024
void filelines_baseline(char *filepath, uint32_t *total_line_num,
                        uint32_t *line_num) {
  int handle;
  if ((handle = open(filepath, O_RDONLY)) < 0)
    return;
  char *bp = (char *)malloc(BLOCK_SIZE);
  if (bp == NULL) {
    close(handle);
    return;
  }
  int cur_len = 0;
  while (1) {
    int bytes_read = read(handle, bp, BLOCK_SIZE);
    if (bytes_read <= 0)
      break;
    for (int i = 0; i < bytes_read; i++) {
      if (bp[i] == '\n') {
        (*total_line_num)++;
        if (cur_len >= MAX_LEN)
          line_num[MAX_LEN - 1]++;
        else
          line_num[cur_len]++;
        cur_len = 0;
      } else {
        cur_len++;
      }
    }
  }
  close(handle);
}

#include <immintrin.h>
#include <string.h>
// 少数一个0和一个最大行
void filelines_vectorize(char *filepath, uint32_t *total_line_num,
                         uint32_t *line_num) {
  int handle;
  if ((handle = open(filepath, O_RDONLY)) < 0)
    return;
  char *bp = (char *)malloc(BLOCK_SIZE);
  if (bp == NULL) {
    close(handle);
    return;
  }
  int cur_len = 0;
  __m256i newline = _mm256_set1_epi8('\n');

  while (1) {
    int bytes_read = read(handle, bp, BLOCK_SIZE);
    if (bytes_read <= 0)
      break;

    int i = 0;
    for (; i <= bytes_read - 32; i += 32) {
      __m256i chunk_1 = _mm256_loadu_si256((__m256i *)&bp[i]);
      __m256i cmp = _mm256_cmpeq_epi8(chunk_1, newline);
      int mask_1 = _mm256_movemask_epi8(cmp);
      int last_pos = 0;
      while (mask_1 != 0) {
        int pos = __builtin_ctz(mask_1);
        (*total_line_num)++;
        if (cur_len + pos - last_pos >= MAX_LEN)
          line_num[MAX_LEN - 1]++;
        else
          line_num[cur_len + pos - last_pos]++;
        cur_len = 0;
        mask_1 = mask_1 & (mask_1 - 1);
        last_pos = pos + 1;
      }
      cur_len += 32 - last_pos;
    }
    // 处理剩余字节
    for (; i < bytes_read; i++) {
      if (bp[i] == '\n') {
        (*total_line_num)++;
        if (cur_len >= MAX_LEN)
          line_num[MAX_LEN - 1]++;
        else
          line_num[cur_len]++;
        cur_len = 0;
      } else {
        cur_len++;
      }
    }
  }
  close(handle);
  free(bp);
}

// struct ThreadData {
//   char *filepath;
//   uint32_t total_line_num;
//   uint32_t line_num[MAX_LEN];
//   int last_line_len;
//   off_t start;
//   off_t end;
// };

// void filelines_thread_func(ThreadData *data) {
//   int handle;
//   if ((handle = open(data->filepath, O_RDONLY)) < 0)
//     return;
//   if (lseek(handle, data->start, SEEK_SET) == (off_t)-1) {
//     close(handle);
//     return;
//   }
//   char *bp = (char *)malloc(BLOCK_SIZE);
//   if (bp == NULL) {
//     close(handle);
//     return;
//   }
//   int cur_len = 0;
//   __m256i newline = _mm256_set1_epi8('\n');

//   while (1) {
//     int bytes_read = read(handle, bp, BLOCK_SIZE);
//     if (bytes_read <= 0 || lseek(handle, 0, SEEK_CUR) > data->end)
//       break;

//     int i = 0;
//     for (; i <= bytes_read - 32; i += 32) {
//       __m256i chunk_1 = _mm256_loadu_si256((__m256i *)&bp[i]);
//       __m256i cmp = _mm256_cmpeq_epi8(chunk_1, newline);
//       int mask_1 = _mm256_movemask_epi8(cmp);
//       int last_pos = 0;
//       while (mask_1 != 0) {
//         int pos = __builtin_ctz(mask_1);
//         data->total_line_num++;
//         if (cur_len + pos - last_pos >= MAX_LEN)
//           data->line_num[MAX_LEN - 1]++;
//         else
//           data->line_num[cur_len + pos - last_pos]++;
//         cur_len = 0;
//         mask_1 = mask_1 & (mask_1 - 1);
//         last_pos = pos + 1;
//       }
//       cur_len += 32 - last_pos;
//     }
//     // 处理剩余字节
//     for (; i < bytes_read; i++) {
//       if (bp[i] == '\n') {
//         data->total_line_num++;
//         if (cur_len >= MAX_LEN)
//           data->line_num[MAX_LEN - 1]++;
//         else
//           data->line_num[cur_len]++;
//         cur_len = 0;
//       } else {
//         cur_len++;
//       }
//     }
//   }
//   data->last_line_len = cur_len;
//   close(handle);
//   free(bp);
// }

// void filelines_multithread(char *filepath, uint32_t *total_line_num,
//                            uint32_t *line_num, int num_threads) {
//   int handle;
//   if ((handle = open(filepath, O_RDONLY)) < 0)
//     return;
//   off_t file_size = lseek(handle, 0, SEEK_END);
//   close(handle);

//   std::vector<std::thread> threads;
//   std::vector<ThreadData> thread_data(num_threads);

//   off_t chunk_size = file_size / num_threads;
//   for (int i = 0; i < num_threads; i++) {
//     thread_data[i].filepath = filepath;
//     thread_data[i].total_line_num = 0;
//     memset(thread_data[i].line_num, 0, sizeof(thread_data[i].line_num));
//     thread_data[i].last_line_len = 0;
//     thread_data[i].start = i * chunk_size;
//     thread_data[i].end = (i == num_threads - 1) ? file_size : (i + 1) * chunk_size;
//     threads.emplace_back(filelines_thread_func, &thread_data[i]);
//   }

//   for (auto &t : threads) {
//     t.join();
//   }

//   // 合并结果
//   for (int i = 0; i < num_threads; i++) {
//     *total_line_num += thread_data[i].total_line_num;
//     for (int j = 0; j < MAX_LEN; j++) {
//       line_num[j] += thread_data[i].line_num[j];
//     }
//   }

//   // 合并最后一行的长度
//   for (int i = 0; i < num_threads - 1; i++) {
//     int combined_len = thread_data[i].last_line_len + thread_data[i + 1].last_line_len;
//     if (combined_len >= MAX_LEN)
//       line_num[MAX_LEN - 1]++;
//     else
//       line_num[combined_len]++;
//   }
// }

