//
// Created by quanyec on 10/20/20.
//

#include <zconf.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <printf.h>
#include "listbuff.h"


void lb_init(lb_buff_t *buff) {
    buff->data = malloc(DEFAULT_BUFFER_SIE);
    buff->data_len = 0;
    buff->total_size = DEFAULT_BUFFER_SIE;
}

void lb_init_in_buff_size(lb_buff_t *buff, size_t buff_size) {
    assert(buff_size > 0);
    buff->data = malloc(buff_size);
    buff->data_len = 0;
    buff->total_size = buff_size;
}

size_t lb_append_array(lb_buff_t *buff, void *arr_data, size_t size) {
    if (buff->total_size - buff->data_len < size) {
        /* `buff->arr_data`的空间无法存放更多内容，申请更多内存 */
        size_t new_data_size = size + 2 * buff->total_size;
        void *new_data = malloc(new_data_size);
        // 复制`buff->arr_data`数据到`new_data`
        memcpy(new_data, buff->data, buff->data_len);
        // 从`new_data`的`buff_len`始复制`arr_data`进`new_data`
        memcpy(new_data + buff->data_len, arr_data, size);
        // 更新`total_size`
        buff->total_size = new_data_size;
        // free掉旧的data
        free(buff->data);
        // 更新buff的新data
        buff->data = new_data;
    } else {
        /* 空间充足，直接添加data */
        memcpy(buff->data + buff->data_len, arr_data, size);
    }
    // 更新`data_len`
    buff->data_len += size;

    return buff->data_len - size;
}

size_t lb_append(lb_buff_t *buff, int data) {
    if (buff->data_len + 1 > buff->total_size) {
        size_t new_data_size = 2 * buff->total_size;
        void *new_data = malloc(new_data_size);
        memcpy(new_data, buff->data, buff->data_len);
        memset(new_data + buff->data_len, data, 1);
        buff->total_size = new_data_size;
        free(buff->data);
        buff->data = new_data;
    } else {
        memset(buff->data + buff->data_len, data, 1);
    }
    buff->data_len += 1;

    return buff->data_len - 1;
}

void lb_free(lb_buff_t *buff) {
    free(buff->data);
}
