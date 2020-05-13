/*;;
 * FILE: http_request.h;
 * Copyright (C) Lunar Eclipse;
 */ 

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <time.h>
#include "http.h"

#define AGAIN EAGAIN

#define HTTP_PARSE_INVALID_METHOD 10
#define HTTP_PARSE_INVALID_REQUEST 11
#define HTTP_PARSE_INVALID_HEADER 12

#define HTTP_UNKNOWN 0x0001
#define HTTP_GET     0x0002
#define HTTP_HEAD    0x0004
#define HTTP_POST    0x0008

#define HTTP_OK 200

#define HTTP_NOT_MODIFIED 304

#define HTTP_NOT_FOUND 404

#define MAX_BUF 8124

typedef struct request_s {
    void* root; //root is a html type file
    int fd;
    int epfd;   //epoll file descriptor
    char buf[MAX_BUF];
    size_t pos, last;
    int state;
    void* req_start;
    void* req_end;
    void* method_end;
    int method;
    void* uri_start;
    void* uri_end;
    void* path_start;
    void* path_end;
    void* query_start;
    void* query_end;
    int http_major; //of HTTP version
    int http_minor;
    
    struct list_head list;
    void* cur_header_key_start;
    void* cur_header_key_end;
    void* cur_header_value_start;
    void* cur_header_value_end;
    
    void* timer;
} request_t;

typedef struct {
    int fd;
    int keep_alive;
    time_t mtime; //the modified time of the file
    int modified; //compart If-modified-since field with mtime to decide whether the file is modified since last time
    int status;
} http_out_t;

typedef struct header_s {
    void* key_start, *key_end;
    void* value_start, *value_end;
    list_head list;
} header_t;

typedef int (*header_handler_ptr)(request_t* req, http_out_t* out, char* data, int len);

typedef struct {
    char* name;
    header_handler_ptr handler;
} header_handle_t;

void handle_header(request_t* req, http_out_t* out);

int http_close_conn(request_t* req);

int init_request(request_t* req, int fd, int epfd, conf_t* cf);

int free_request(request_t* req);

int init_out(http_out_t* out, int fd);

int free_out(http_out_t* out);

const char* get_shortmsg_from_status_code(int status_code);

extern header_handle_t http_headers_in[];

#endif
