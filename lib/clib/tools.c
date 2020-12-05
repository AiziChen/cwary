//
// Created by quanye on 11/23/20.
//

#include "tools.h"
#include "listbuff.h"

void *get_pointer(void *v) {
    return v;
}

int str_index_in_lowercase(const char *s, int s_len, char *s2) {
    size_t s2_len = strlen(s2);
    if (s2_len == 0) {
        return -1;
    }

    unsigned total = 0;
    int i, j;
    for (i = 0; i < s_len; ++i) {
        for (j = 0; j < s2_len && i + j < s_len; ++j) {
            if (tolower(s[i + j]) == s2[j]) {
                total++;
                if (total == s2_len) {
                    return i;
                }
            } else {
                total = 0;
                break;
            }
        }
    }
    return -1;
}