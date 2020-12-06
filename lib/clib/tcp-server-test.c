//
// Created by quanye on 12/7/20.
//

#include <errno.h>
#include "tcp-server.h"

/*****************************/
/************ TEST ***********/
/*****************************/
void *handle_connection_cb(SOCKET socket_client, size_t *data) {
    /*------------process response header------------*/
    printf("Reading header...\n");
//    printf("%.*s", data->data_len, data->data);

    /*-----------responding data to the client------------*/
    printf("Sending response...\n");
    // Send response header & data
    char *rheader = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/plain\r\n"
                    "Content-Length: 12\r\n\r\n";
    ssize_t bytes_sent = send(socket_client, rheader, strlen(rheader), 0);
    printf("Sent %zd of %lu bytes.\n", bytes_sent, strlen(rheader));
    bytes_sent = send(socket_client, "HELLO, WORLD", 12, 0);
    printf("Sent %zd of %lu bytes.\n", bytes_sent, strlen(rheader));

    return NULL;
}

int main(void) {
    printf("%s\n", strerror(EINTR));
//    SOCKET socket_listen = do_init_and_bind("127.0.0.1", "8080");
//    if (socket_listen == -1) {
//        return -1;
//    }
//
//    web_loop(socket_listen, handle_connection_cb);
//
//    printf("Closing listening socket...\n");
//    CLOSE_SOCKET(socket_listen);
//
//    printf("Finished.\n");

    return 0;
}
