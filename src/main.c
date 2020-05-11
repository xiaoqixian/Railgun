/*
 * FILE: main.c
 * Copyright (C) Lunar Eclipse
 * Copyright (C) https://github.com/xiaoqixian
 * Copyright (C) Railgun
 */

#include <stdint.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "util.h"
#include "timeer.h"
#include "http.h"
#include "epoll.h"
#include "threadpool.h"
#include "figure.h"

#define CONF "railgun.conf"
#define RAILGUN_VERSION "1.0"
#define PROJECT_NAME "RAILGUN"

extern struct epoll_event* *events;

static const struct option long_options[] = {
    {"help", no_argument, NULL, '?'},
    {"version", no_argument, NULL, 'v'},
    {"conf", optional_argument, NULL, 'c'},
    {NULL, 0, NULL, 0}
};

static void give_options() {
    fprintf(stderr,
            "Railgun [options]...\n"
            "   -c|--conf <config file> Specify config file. Default ../conf/railgun.conf\n"
            "   -?|-h|--help This information\n"
            "   -v|--version Display program version\n"
           );
}

int main(int argc, char* argv[]) {
    int res, opt = 0;
    int option_index = 0;
    char* conf_file = CONF;
    
    //parse command line arguments
    if (argc == 1) {
        printf("-----Welcome to railgun!-----\n" "Use <-h> option to get more information\n");
    }
    else {
        printf("-----Welcome to railgun!-----");
        print_str(PROJECT_NAME);
    }

    while ((opt = getopt_long(argc, argv, "vc::?h", long_options, &option_index)) != EOF) {
        switch (opt) {
            case '0': break;
            case 'c':
                conf_file = optarg;
                break;
            case 'v':
                printf("Railgun Version--"RAILGUN_VERSION"\n");
                return 0;
            case '?':
            case 'h':
            case ':':
                give_options();
                return 0;
        }
    }
    
    DEBUG("conf_file = %s", conf_file);
    
    if (optind < argc) {
        LOG_ERR("non-option ARGV-elements: ");
        while (optind < argc) {
            LOG_ERR("%s ", argv[optind++]);
        }
        return 0;
    }
    
    //read conf file
    char conf_buf[BUFLEN];
    conf_t cf;
    res = read_conf(conf_file, &cf, conf_buf, BUFLEN);
    CHECK(res == CONF_OK, "read conf err");
    
    /*
     * install signal handle for SIGPIPE
     * when a fd is closed by remote, writing to this fd will cause
     * system send SIGPIPE to this process, which exit the program
     */
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    if (sigaction(SIGPIPE, &sa, NULL)) {
        LOG_ERR("install signal handler for SIGPIPE failed");
        return 0;
    }
    
    //initialize listening socket
    int listen_fd;
    struct sockaddr_in client_addr;
    socklen_t inlen = 1;
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    
    listen_fd = open_listenfd(cf.port);
    res = make_socket_non_blocking(listen_fd);
    CHECK(res == 0, :"make_socket_non_blocking");
    
    //create epoll and add listen_fd to epoll
    int epfd = epoll_create(0);
    struct epoll_event event;
    
    request_t* req = (request_t*)malloc(sizeof(struct request_t));
    init_request(req, listen_fd, epfd, &cf);
    
    event.data.ptr = (void*)req;
    event.events = EPOLLIN | EPOLLET;
    epoll_add(epfd, listen_fd, &event);
    
    //create thread pool
    timer_init();
    LOG_INFO("railgun started");
    int n;
    int i, fd;
    int time;
    
    //epoll_wait loop
    while (1) {
        time = find_timer();
        DEBUG("wait time = %d", time);
        n = epoll_wait(epfd, events, MAXEVENTS, time);
        handle_expire_timers();
        
        for (i = 0; i < n; i++) {
            request_t* r = (request_t*)events[i].data.ptr;
            fd = r->fd;
            
            if (listen_fd == fd) {
                int infd;
                while (1) {
                    infd = accept(listen_fd, (struct sockaddr*)&client_addr, &inlen);
                    if (infd < 0) {
                        if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                            break;
                        }
                        else {
                            LOG_ERR("accept");
                            break;
                        }
                    }
                    
                    res = make_socket_non_blocking(infd);
                    CHECK(res == 0, "make_socket_non_blocking");
                    LOG_INFO("new connectino fd %d", infd);
                    
                    request_t* request = (request_t*)malloc(sizeof(struct request_t));
                    if (request == NULL) {
                        LOG_ERR("malloc request_t failed");
                        break;
                    }
                    
                    init_reuqest(request, infd, epfd, &cf);
                    event.data.ptr = (void*)request;
                    event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;

                    epoll_add(epfd, infd, &event);
                    add_timer(request, TIMEOUT_DEFAULT, http_close_conn);
                }
            }
            else {
                if ((events[i].events & EPOLLERR) ||    
                    (events[i].events & EPOLLHUP) ||
                    (!(events[i].events & EPOLLIN))) {
                    LOG_ERR("epoll error fd: %d", r->fd);
                    close(fd);
                    continue;
                }
                LOG_INFO("new data from fd %d", fd);
                
                do_request(events[i].data.ptr);
            }
        }
    }

    return 0;
}
