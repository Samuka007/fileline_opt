#include "find_most_freq.h"
// #include <algorithm>
// #include <cstdint>
// #include <span>

void find_most_freq_line(uint32_t *line_num,uint32_t *most_freq_len,uint32_t *most_freq_len_linenum){
    int t_linenum=0;
    int t_len=0;
    for(int i=0;i<MAX_LEN;i++){
        if(line_num[i]>t_linenum){
            t_linenum=line_num[i];
            t_len = i;
        }
    }
    *most_freq_len=t_len;
    *most_freq_len_linenum = t_linenum;
}

// std::pair<uint32_t, uint32_t> find_most_freq_line(std::span<uint32_t, MAX_LEN> line_num) {
//     auto max = std::max_element(line_num.begin(), line_num.end());
//     return {max - line_num.begin(), *max};
// }