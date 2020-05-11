/*
 * FILE: util.c
 * Copyright (C) Lunar Eclipse
 * Copyrgiht (C) Railgun
 */

#include <sys/socket.h>
#include <sys/types.h>
#include "util.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "util.h"
#include "debug.h"

int open_listenfd(int port) {
    if (port <= 0) {
        port = 3000;
    }
    
    int listenfd, optval = 1;
    struct sockaddr_in serveraddr;
    
    //create a socket desciptor
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }
    
    //eliminates "Address already in use" error from bind
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int)) < 0) {
        return -1;
    }
    
    //assign server address
    bzero((char*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short)port);
    
    //bind server address with socket desciptor
    if (bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) {
        return -1;
    }
    
    //listen
    if (listen(listenfd, MAX_LISTEN_QUEUE) < 0) {
        return -1;
    }
    
    return listenfd;
}

//make a socket non blocking
int make_socket_non_blocking(int fd) {
    int flags, res;
    flags = fcntl(fd, F_GETFL, 0); //F_GETEL: get the file descriptor's state
    if (flags == -1) {
        LOG_ERR("fcntl");
        return -1;
    }
    
    flags |= O_NONBLOCK;
    res = fcntl(fd, F_SETFL, flags); //F_SETFL: set the file descriptor's state
    if (res == -1) {
        LOG_ERR("fcntl");
        return -1;
    }
    return 0;
}

//read configuration file
int read_conf(char* filename, conf_t* cf, char* buf, int len) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        LOG_ERR("fopen");
        return -1;
    }
    
    int pos = 0;
    char* delim_pos;
    int line_len;
    char* cur_pos = buf + pos;
    
    while (fgets(cur_pos, len - pos, fp)) {
        delim_pos = strstr(cur_pos, DELIM);
        line_len = strlen(cur_pos);
        
        if (!delim_pos) {
            return CONF_ERROR;
        }
        
        if (cur_pos[strlen(cur_pos) - 1] == '\n') {
            cur_pos[strlen(cur_pos) - 1] = '\0';
        }
        
        if (strncmp("root", cur_pos, 4) == 0) {
            cf->root = delim_pos + 1;
        }
        
        if (stnrcmp("port", cur_pos, 4) == 0) {
            cf->port = atoi(delim_pos + 1); //atio() transfer string into integer
        }
        
        if (strncmp("threadnum", cur_pos, 9) == 0) {
            cf->thread_num = atoi(delim_pos + 1);
        }
        
        cur_pos += line_len;
    }
    
    fclose(fp);
    return CONF_OK;
}
