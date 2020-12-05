//
// Socket-server and Socket-client
//
#include "tcp-server.h"
#include "listbuff.h"
#include "tools.h"

#define RECV_MAX 65536
static int loop = 1;

struct addrinfo *init_addrinfo(const char *hostname, const char *servname) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6;                 /* AF_INET6 both support ipv6 and ipv4 */
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *info;
    if (getaddrinfo(hostname, servname, &hints, &info) != 0) {
        perror("getaddrinfo() failed");
        return NULL;
    }
    return info;
}

size_t do_socket(struct addrinfo *addrinfo) {
    SOCKET socket_fd;
    socket_fd = socket(addrinfo->ai_family, addrinfo->ai_socktype, addrinfo->ai_protocol);
    if (!ISVALID_SOCKET(socket_fd)) {
        perror("socket() failed");
        return -1;
    }
    /* enable dual-stack sockets: for supporting ipv4 and ipv6 */
    int option = 0;
    if (setsockopt(socket_fd, IPPROTO_IPV6, IPV6_V6ONLY, (void *) &option, sizeof(option)) != 0) {
        perror("setsockopt() failed");
        return -1;
    }
    return socket_fd;
}

SOCKET do_init_and_bind(char *hostname, char *servname) {
    printf("Configuring local address...\n");
    struct addrinfo *bind_address = init_addrinfo(NULL, servname);

    printf("Creating socket...\n");
    size_t socket_listen = do_socket(bind_address);

    printf("Binding socket to local address...\n");
    if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen)) {
        perror("bind() failed");
        return -1;
    }
    freeaddrinfo(bind_address);

    printf("Listening...\n");
    if (listen(socket_listen, 10) < 0) {
        perror("listen() failed");
        return -1;
    }
    return socket_listen;
}

SOCKET do_accept(SOCKET socket_listen) {
    printf("Waiting for connection...\n");
    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);
    SOCKET socket_client = accept(socket_listen, (struct sockaddr *) &client_address, &client_len);
    if (!ISVALID_SOCKET(socket_client)) {
        perror("accept() failed");
        return -1;
    }

    printf("Client is connected...\n");
    char host_buf[NI_MAXHOST], serv_buf[NI_MAXSERV];
    getnameinfo((struct sockaddr *) &client_address, client_len, host_buf, NI_MAXHOST, serv_buf, NI_MAXSERV,
                NI_NUMERICHOST);
    printf("host: %s, serv: %s\n", host_buf, serv_buf);

    return socket_client;
}

void handle_connection(SOCKET socket_client, void *(handle_connection_cb)(SOCKET, size_t *)) {
    printf("Reading request...\n");

    lb_buff_t *bytes_data = malloc(sizeof(lb_buff_t));
    lb_init_in_buff_size(bytes_data, RECV_MAX);

    int buf[RECV_MAX];
    int has_read;
    while ((has_read = recv(socket_client, buf, RECV_MAX, 0)) > 0) {
        lb_append_array(bytes_data, buf, has_read);
        // Process the HTTP's header
        // TODO: minor bug in `has_read < RECV_MAX`
        if (has_read < RECV_MAX) {
            // Handle this connection
            handle_connection_cb(socket_client, bytes_data->data);
            // re-init the lb_buffer
            lb_free(bytes_data);
            lb_init_in_buff_size(bytes_data, RECV_MAX);
        }
    }
    lb_free(bytes_data);
    free(bytes_data);
//    printf("%.*s", bytes_data->data_len, bytes_data->data);
}

void *handle(void *arg) {
    ssize_t *args = (ssize_t *) *((ssize_t *) arg);
    SOCKET socket_client = *args;
    void *handle_conn_callback = (void *) *(args + 1);

    handle_connection(socket_client, handle_conn_callback);

    printf("Closing connection...\n");
    CLOSE_SOCKET(socket_client);
    free(args);

    return NULL;
}

void web_loop(SOCKET socket_listen, void *handle_conn_callback) {
    while (loop) {
        SOCKET socket_client = do_accept(socket_listen);
        if (socket_client == -1) {
            perror("web_loop() and waiting failed, retrying...");
            sleep(1);
            continue;
        }

        ssize_t *args = malloc(sizeof(ssize_t) * 2);
        args[0] = socket_client;
        args[1] = (ssize_t) handle_conn_callback;

        pthread_t t;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&t, &attr, handle, &args);
        pthread_detach(t);
    }
}


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
    SOCKET socket_listen = do_init_and_bind("127.0.0.1", "8080");
    if (socket_listen == -1) {
        return -1;
    }

    web_loop(socket_listen, handle_connection_cb);

    printf("Closing listening socket...\n");
    CLOSE_SOCKET(socket_listen);

    printf("Finished.\n");

    return 0;
}
