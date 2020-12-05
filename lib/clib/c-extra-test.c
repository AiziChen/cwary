//
// Created by quanye on 12/5/20.
//

#include <stdio.h>
#include "c-extra.h"

int main(void)
{
    char payload[1024] = "HTTP/1.1 200 OK\r\n"
                        "Server: GitHub.com\r\n"
                        "Date: Fri, 04 Dec 2020 16:25:48 GMT\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: 0\r\n"
                        "Status: 200 OK\r\n"
                        "Cache-Control: no-cache\r\n"
                        "X-RateLimit-Limit: 60\r\n"
                        "X-RateLimit-Remaining: 60\r\n"
                        "X-RateLimit-Reset: 1607102748\r\n"
                        "X-RateLimit-Used: 0\r\n"
                        "X-GitHub-Media-Type: github.v3; format=json\r\n"
                        "Access-Control-Allow-Origin: *\r\n"
                        "Strict-Transport-Security: max-age=31536000; includeSubdomains; preload\r\n"
                        "X-Frame-Options: deny\r\n"
                        "X-Content-Type-Options: nosniff\r\n"
                        "X-XSS-Protection: 1; mode=block\r\n"
                        "Referrer-Policy: origin-when-cross-origin, strict-origin-when-cross-origin\r\n"
                        "Content-Security-Policy: default-src 'none'\r\n"
                        "Vary: Accept-Encoding, Accept, X-Requested-With\r\n"
                        "X-GitHub-Request-Id: 875E:3730:B92A58:139A925:5FCA630B\r\n\r\nHello, World";

    char* header_sobj = parse_header_to_sobj(payload);
    printf("%s\n", header_sobj);

    free(header_sobj);

    return 0;
}