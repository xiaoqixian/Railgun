/*
 * FILE: catch_req.c
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Railgun
 * Description: Listen the 9000 port the localhost to catch what the 
 * browser send when input "localhost:9000" in the address bar.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>

#define CHECK(A, M, ...) if ((A)) {fprintf(stderr, "[ERROR] errno:%s" M "\n", strerror(errno), ##__VA_ARGS__);}

#define PORT 9000
#define BUFFER 1024

int main() {
    int server_sock, res, client_sock;
    struct sockaddr_in server_addr, client_addr;
    
    //create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    CHECK(server_sock < 0, "server socket create failed");
    
    //assign the server_addr
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    res = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    CHECK(res < 0, "bind error");
    
    res = listen(server_sock, 1);
    CHECK(res < 0, "listen error");
    
    socklen_t addrlen = sizeof(struct sockaddr);
    for (;;) {
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addrlen);
        if (client_sock < 0)
            continue;
        else
            break;
    }
    
    char buffer[BUFFER];
    size_t size;
    for (;;) {
        size = read(client_sock, buffer, BUFFER);
        if (size > 0) {
            write(1, buffer, size);
            break;
        }
    }
    close(server_sock);
    close(client_sock);
    return 0;
}
