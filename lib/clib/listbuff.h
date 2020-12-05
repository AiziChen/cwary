//
// Created by quanye on 10/20/20.
//

#ifndef MYCLIB_LISTBUFF_H
#define MYCLIB_LISTBUFF_H

#endif //MYCLIB_LISTBUFF_H

#define DEFAULT_BUFFER_SIE 10

/* lb_buff_t */
typedef struct {
    void *data;
    size_t data_len;
    size_t total_size;
    size_t pos;
} lb_buff_t;


/**
 * 使用默认长度的buff为lb_buff分配长度空间
 * @param buff 刚初始化的 lb_buff
 */
void lb_init(lb_buff_t *buff);

/**
 * 指定长度为`buff-size`的 lb_buff
 * @param buff 刚初始化的 lb_buff
 * @param buff_size lb_buff的大小
 */
void lb_init_in_buff_size(lb_buff_t *buff, size_t buff_size);

/**
 * 添加`array-data`到`buff`末尾
 * @param buff `lb_buff_t`类型的对象
 * @param arr_data array型数据
 * @param size 需要复制的array的长度
 * @return 还未添加`array-data`时的`buff`的末尾
 */
size_t lb_append_array(lb_buff_t *buff, void *arr_data, size_t size);

size_t lb_append(lb_buff_t *buff, int data);

void lb_free(lb_buff_t *buff);