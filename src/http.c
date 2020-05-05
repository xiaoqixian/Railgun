/*
 * FILE: http.c
 * Copyright (C) Lunar Eclipse
 */

#include <strings.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "http.h"
#include "http_parse.h"
#include "http_request.h"
#include "epoll.h"
#include "error.h"
#include "timer.h"

static const char* get_file_type(const char* type);

static void parse_uri(char* uri, int length, char* filename, char* query_string);

static void do_error(int fd, char* cause, char* errnum, char* shortmsg, char* longmag);

static void serve_static(int fd, char* filename, size_t filesize, http_out_t* out);

static char* ROOT = NULL;

mime_type_t mime[] = 
{
    {".html", "text/html"},
    {".xml", "text/xml"},
    {".xhtml", "application/xhtml+xml"},
    {".txt", "text/plain"},
    {".rtf", "application/rtf"},
    {".pdf", "application/pdf"},
    {".word", "application/msword"},
    {".png", "image/png"},
    {".gif", "image/gif"},
    {".jpg", "image/jpeg"},
    {".jpeg", "image/jpeg"},
    {".au", "audio/basic"},
    {".mpeg", "video/mpeg"},
    {".mpg", "video/mpeg"},
    {".avi", "video/x-msvideo"},
    {".gz", "application/x-gzip"},
    {".tar", "application/x-tar"},
    {".css", "text/css"},
    {NULL, "text/plain"} 
};

void do_request(void* ptr) {
    http_req_t* req = (http_req_t*)ptr;
    int fd = req->fd;
    int res, n;
    char filename[SHORTLINE];
    struct stat sbuf;
    ROOT = req->root;
    char* plast = NULL;
    size_t remain_size;
    
    del_timer(req);
    for (;;) {

    }
}
