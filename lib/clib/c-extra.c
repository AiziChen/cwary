//
// Created by quanye on 11/27/20.
//

#include "c-extra.h"
#include "listbuff.h"

char *get_error(void) {
    extern int errno;
    return strerror(errno);
}

char *get_string(void *s) {
    return s;
}

char *parse_header_to_sobj(char *header) {
    lb_buff_t lb_buff;
    lb_buff_t *buff = &lb_buff;
    lb_init_in_buff_size(buff, 512);
    lb_append_array(buff, "(*obj", 5);
    char *p = strtok(header, "\r\n");
    while (p != NULL) {
        lb_append(buff, '(');
        lb_append_array(buff, p, strlen(p));
        lb_append(buff, ')');
        p = strtok(NULL, "\r\n");
    }
    return buff->data;
}
