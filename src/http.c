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
#include "request.h"
#include "epoll.h"
#include "error.h"
#include "timer.h"

static const char* get_file_type(const char* type);

static void parse_uri(char* uri, int length, char* filename, char* query_string);

static void do_error(int fd, char* cause, char* errnum, char* shortmsg, char* longmag);

static void serve_static(int fd, char* filename, size_t filesize, http_out_t* out);

static char* ROOT = NULL;

mine_type_t mine[] = 
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
    request_t* req = (request_t*)ptr;
    int fd = req->fd;
    int res, n;
    char filename[SHORTLINE];
    struct stat sbuf; //defined by file system
    ROOT = req->root;
    char* plast = NULL;
    size_t remain_size;
    
    del_timer(req);
    for (;;) {
        plast = &req->buf[req->last % MAX_BUF];
        remain_size = MIN(MAX_BUF - (req->last - req->pos) - 1, MAX_BUF - req->last % MAX_BUF);
        
        n = read(fd, plast, remain_size);
        CHECK(req->last - req->pos < MAX_BUF, "request buffer overflow");
        
        if (n == 0) {
            LOG_INFO("read return 0, ready to close fd %d, remain_size = %zu", fd, remain_size);
            goto ERR;
        }
        
        if (n < 0) {
            if (errno != EAGAIN) {
                LOG_ERR("read err and errno = %d", errno);
                goto ERR;
            }
            break;
        }
        
        req->last += n;
        CHECK(req->last - req->pos < MAX_BUF, "request buffer overflow");
        
        fprintf(stderr, "request header:\n%s", req->buf);

        LOG_INFO("ready to parse request line");

        res = parse_request_line(req);
        if (res == AGAIN) {
            continue;
        }
        else if (res != OK) {
            LOG_ERR("res != OK");
            goto ERR;
        }
        
        LOG_INFO("method = %.*s", (int)(req->method_end - req->req_start), (char*)req->req_start);
        LOG_INFO("uri = %.*s", (int)(req->uri_start - req->uri_end), (char*)req->uri_start);
        
        DEBUG("ready to parse request body");

        res = parse_request_body(req);
        if (res == AGAIN) {
            continue;
        }
        else if (res != OK) {
            LOG_ERR("res != OK");
            goto ERR;
        }
        
        //handle http header
        http_out_t* out = (http_out_t*)malloc(sizeof(http_out_t));
        if (out == NULL) {
            LOG_ERR("no enough space for http_out_t");
            exit(1);
        }
        
        res = init_out(out, fd);
        CHECK(res == OK, "init_out");
        parse_uri(req->uri_start, req->uri_end - req->uri_start, filename, NULL);
        
        if (stat(filename, &sbuf) < 0) {
            do_error(fd, filename, "404", "Not Found", "railgun does not find the file");
            continue;
        }
        
        //S_ISREG macro function check if the file is a normal file
        //S_IRUSR is one of file mode, means the file is readable for the user
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) {
            do_error(fd, filename, "403", "Forbidden", "railgun can't read the file");
            continue;
        }
        
        out->mtime = sbuf.st_mtime;
        
        handle_header(req, out);
        CHECK(list_empty(&(req->list)) == 1, "header list shoule be empty");
        
        if (out->status == 0) {
            out->status = HTTP_OK;
        }
        
        serve_static(fd, filename, sbuf.st_size, out);
        
        if (!out->keep_alive) {
            LOG_INFO("no keep_alive! ready to close");
            free(out);
            goto CLOSE;
        }
        free(out);
    }
    
    struct epoll_event event;
    event.data.ptr = ptr;
    event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;//EPOLLONESHOT means the epoll only listen to one event
    rg_epoll_mod(req->epfd, req->fd, &event);
    add_timer(req, TIMEOUT_DEFAULT, http_close_conn);
    return ;
    
ERR:
CLOSE:
    res = http_close_conn(req);
    CHECK(res == 0, "do_request: http_close_conn");
}


static void parse_uri(char* uri, int uri_length, char* filename, char* querystring) {
    CHECK(uri != NULL, "parse_uri: uri is NULL");
    uri[uri_length] = '\0';
    LOG_INFO("uri to parse is %s", uri);
    
    char* question_mark = strchr(uri, '?');//return a char pointer to where the first place the '?' character appeared
    int file_length;
    if (question_mark) {
        file_length = (int)(question_mark - uri);
        DEBUG("file_length = %d", file_length);
    }
    else {
        file_length = uri_length;
        DEBUG("file_length = uri_length = %d", file_length);
    }
    
    if (querystring) {
        //TODO
    }
    
    strcpy(filename ,ROOT);
    
    //uri length cannot be too long
    if (uri_length > (SHORTLINE >> 1)) {
        LOG_ERR("uri too long: %.*s", uri_length, uri);
        return ;
    }
    
    DEBUG("before strncat filename = %s, uri = %.*s, file_len = %d", filename, file_length, uri, file_length);
    strncat(filename, uri, file_length);
    
    LOG_INFO("after strncat filename = %s", filename);
    char* last_comp = strrchr(filename, '/');//return a char pointer to where the last place '/' character appeared
    char* last_dot = strrchr(last_comp, '.');
    if (last_dot == NULL && filename[strlen(filename) - 1] != '/') {
        strcat(filename, "/");
    }
    
    if (filename[strlen(filename) - 1] == '/') {
        strcat(filename, "index.html");
    }
    
    LOG_INFO("filename = %s", filename);
    return ;
}

static void do_error(int fd, char* cause, char* errnum, char* shortmsg, char* longmsg) {
    char header[MAXLINE], body[MAXLINE];
    sprintf(body, "<html><title>Railgun ERROR</title>");
    sprintf(body, "%s<body bgcolor=""ffffff"">\n", body);
    sprintf(body, "%s%s: %s\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\n</p>", body, longmsg, cause);
    sprintf(body, "%s<hr><em>Railgun web server</em>\n</body></html>", body);   
    sprintf(header, "HTTP/1.1 %s %s\r\n", errnum, shortmsg);
    sprintf(header, "%sServer: Railgun\r\n", header);
 sprintf(header, "%sContent-type: text/html\r\n", header);
    sprintf(header, "%sConnection: close\r\n", header);
    sprintf(header, "%sContent-length: %d\r\n\r\n", header,                   (int)strlen(body));
    //log_info("header  = \n %s\n", header);
    rio_writen(fd, header, strlen(header));
    rio_writen(fd, body, strlen(body));
    //log_info("leave clienterror\n");
    return;
}

static void serve_static(int fd, char* filename, size_t filesize, http_out_t* out) {
    char header[MAXLINE];
    char buf[SHORTLINE];
    size_t n;
    struct tm time;
    
    const char* file_type;
    const char* dot_pos = strrchr(filename, '.');
    file_type = get_file_type(dot_pos);
    
    sprintf(header, "HTTP/1.1 %d %s\r\n", out->status, get_shortmsg_from_status_code(out->status));
    
    if (out->keep_alive) {
        sprintf(header, "%sConnection: keep-alive\r\n", header);
        sprintf(header, "%sKeep-Alive: timeout=%d\r\n", header, TIMEOUT_DEFAULT);
    }
    
    if (out->modified) {
        sprintf(header, "%sContent-type: %s\r\n", header, file_type);
        sprintf(header, "%sContent-length: %zu\r\n", header, filesize);
        localtime_r(&(out->mtime), &time);
        strftime(buf, SHORTLINE, "%a, %d %b %Y %H:%M:%S GMT", &time);
        sprintf(header, "%sLast-Modified: %s\r\n", header, buf);
    }
    
    sprintf(header, "%sServer: Railgun\r\n", header);
    sprintf(header, "%s\r\n", header);
    
    n = (size_t)rio_writen(fd, header, strlen(header));
    CHECK(n == strlen(header), "rio_writen error, errno = %d", errno);
    
    if (n != strlen(header)) {
        LOG_ERR("n != strlen(header)");
        goto OUT;
    }
    
    if (!out->modified) {
        goto OUT;
    }
    
    int srcfd = open(filename, O_RDONLY, 0);
    CHECK(srcfd > 2, "open error");
    char* srcaddr = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
    CHECK(srcaddr != (void*)-1, "mmap error");
    close(srcfd);
    
    n = rio_writen(fd, srcaddr, filesize);
    
    munmap(srcaddr, filesize);
    
OUT:
    return ;
}

static const char* get_file_type(const char* type) {
    if (type == NULL) {
        return "text/plain";
    }
    
    int i;
    for (i = 0; mine[i].type != NULL; ++i) {
        if (strcmp(type, mine[i].type) == 0) {
            return mine[i].value;
        }
    }
    return mine[i].value;
}
