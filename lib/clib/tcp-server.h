//
// Created by quanye on 9/12/20.
//

#ifndef TEST_C_COMMON_H
#define TEST_C_COMMON_H

#endif //TEST_C_COMMON_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <printf.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define ISVALID_SOCKET(s) ((s) >= 0)
#define CLOSE_SOCKET(s) close(s)
#define SOCKET ssize_t