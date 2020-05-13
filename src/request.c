/*
 * FILE: request.c
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Railgun
 */

#ifndef _GUN_SOURCE
/* the reason to define _GNU_SOURCE: http://stackoverflow.com/questions/15334558/compiler-gets-warnings-when-using-strptime-function-ci 
 * Seems you have to define _GNU_SOURCE before you include <time.h>
 */

#define _GNU_SOURCE
#endif

#include <math.h>
#include <time.h>
#include <unistd.h>
#include "http.h"
#include "request.h"
#include "error.h"

static int process_ignore(request_t* req, http_out_t* out, char* data, int len);

static int process_connection(request_t* req, http_out_t* out, char* data, int len);

static int process_if_modified_since(request_t* req, http_out_t* out, char* data, int len);

header_handle_t http_headers_in[] = {
    {"Host", process_ignore},
    {"Connection", process_connection},
    {"If-Modified-Since", process_if_modified_since},
    {"", process_ignore}
};

int init_request(request_t* req, int fd, int epfd, conf_t* cf) {
    req->fd = fd;
    req->epfd = epfd;
    req->pos = req->last = 0;
    req->state = 0;
    req->root = cf->root;
    INIT_LIST_HEAD(&(req->list));
    
    return OK;
}

int free_request(request_t* req) {
    // TODO
    (void) req; //doubt
    return OK;
}

int init_out(http_out_t* out, int fd) {
    out->fd = fd;
    out->keep_alive = 0;
    out->modified = 1;
    out->status = 0;
    
    return OK;
}

int free_out(http_out_t* out) {
    (void) out;
    return OK;
}

void handle_header(request_t* req, http_out_t* out) {
    list_head* pos;
    header_t* hd;
    header_handle_t* header_in;
    int len;
    
    LIST_FOR_EACH(pos, &(req->list)) {
        hd = LIST_ENTRY(pos, header_t, list);
        
        for (header_in = http_headers_in;
            strlen(header_in->name) > 0;
            header_in++) {
            if (strncmp(hd->key_start, header_in->name, hd->key_end - hd->key_start) == 0) {
                len = hd->value_end - hd->value_start;
                (*(header_in->handler))(req, out, hd->value_start, len);
                break;
            }
        }
        
        //delete it from the original list
        list_del(pos);
        free(hd);
    }
}

int http_close_conn(request_t* req) {
    close(req->fd);
    free(req);
    
    return OK;
}

static int process_ignore(request_t* req, http_out_t* out, char* data, int len) {
    (void) req;
    (void) out;
    (void) data;
    (void) len;
    return OK;
}

static int process_connection(request_t* req, http_out_t* out, char* data, int len) {
    (void) req;
    if (strncasecmp("keep-alive", data, len) == 0) {
        out->keep_alive = 1;
    }
    
    return OK;
}

static int process_if_modified_since(request_t* req, http_out_t* out, char* data, int len) {
    (void) req;
    (void) len;
    
    struct tm tm; //struct tm is defined in <time.h>
    if (strptime(data, "%a, %d %b %Y %H:%M:%S GMT", &tm) == (char*)NULL) {
        return OK;
    }
    
    time_t client_time = mktime(&tm);
    
    double time_diff = difftime(out->mtime, client_time);
    if (fabs(time_diff) < 1e-6) {
        out->modified = 0;
        out->status = HTTP_NOT_FOUND;
    }
    
    return OK;
}

const char* get_shortmsg_from_status_code(int status_code) {
    if (status_code == HTTP_OK) {
        return "OK";
    }

    if (status_code == HTTP_NOT_FOUND) {
        return "Not Found";
    }

    if (status_code == HTTP_NOT_MODIFIED) {
        return "Not Modified";
    }

    return "Unknown";
}

