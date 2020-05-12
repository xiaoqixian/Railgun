/*
 * FILE: http_parse.c
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Railgun
 */

#include "http.h"
#include "http_parse.h"
#include "error.h"

int parse_request_line(request_t* req) {
    u_char ch, *p, *m; //u_char = unsigned char
    size_t pi;
    
    enum {
        re_start = 0,
        re_method,
        re_spaces_before_uri,
        re_after_slash_in_uri,
        re_http,
        re_http_H,
        re_http_HT,
        re_http_HTT,
        re_http_HTTP,
        re_first_major_digit,
        re_major_digit,
        re_first_minor_digit,
        re_spaces_after_digit,
        re_almots_done
    } state;
    
    state = req->state;
    
    for (pi = req->pos; pi < req->last; pi++) {
        p = (u_char*)&req->buf[pi % MAX_BUF];
        ch = *p;
        
        switch (state) {
            case re_start:
                req->request_start = p;
                
                if (ch == CR || ch == LF) {
                    break;
                }
                
                if ((ch < 'A' || ch > 'Z') && ch != '_') {
                    return HTTP_PARSE_INVALID_METHOD;
                }
                
                state = re_method;
                break;

            case re_method:
                if (ch == ' ') { //A space indicates the method name has ended.
                    req->method_end = p;
                    m = req->request_start;
                    
                    switch (p - m) {
                        case 3: //if the length of the method name is 3
                            if (STR4_CMP(m, 'G', 'E', 'T', ' ')) {
                                req->method = HTTP_GET;
                                break;
                            }
                            break;
                        
                        case 4:
                            if (STR4_CMP(m, 'P', 'O', 'S', 'T')) {
                                req->method = HTTP_POST;
                                break;
                            }
                            
                            if (STR4_CMP(m, 'H', 'E', 'A', 'D')) {
                                req->method = HTTP_HEAD;
                                break;
                            }
                            break;
                            
                        default:
                            req->method = HTTP_UNKNOWN;
                            break;
                    }
                    state = re_spaces_before_uri;
                    break;
                }
                
                if ((ch < 'A' || ch > 'Z') && ch != '_') {
                    return HTTP_PARSE_INVALID_METHOD;
                }
                break;
                
            case re_spaces_before_uri:
                if (ch == '/') {
                    req->uri_start = p;
                    state = re_after_slash_in_uri; //slash is /
                    break;
                }
                
                switch (ch) {
                    case ' ':
                        break;
                    default:
                        return HTTP_PARSE_INVALID_REQUEST;
                }
                break;
                
            case re_after_slash_in_uri:
                switch (ch) {
                    case ' ':
                        req->uri_end = p;
                        state = re_http;
                        break;
                    default:
                        break;
                }
                break;
                
            case re_http:
                switch (ch) {
                    case ' ':
                        break;
                    case 'H':
                        state = re_http_H;
                        break;
                    default:
                        return HTTP_PARSE_INVALID_REQUEST;
                }
                break;
                
            case re_http_H:
                switch (ch) {
                    case 'T':
                        state = re_http_HT;
                        break;
                    default:
                        return HTTP_PARSE_INVALID_REQUEST;
                }
                break;
                
            case re_http_HT:
                switch (ch) {
                    case 'T':
                        state = re_http_HTT;
                        break;
                    default:
                        return HTTP_PARSE_INVALID_REQUEST;
                }
                break;

            case re_http_HTT:
                switch (ch) {
                    case 'P':
                        state = re_http_HTTP;
                        break;
                    default:
                        return HTTP_PARSE_INVALID_REQUEST;
                }
                break;
                
            case re_http_HTTP:
                switch (ch) {
                    case '/':
                        state = re_first_major_digit;
                        break;
                    default:
                        return HTTP_PARSE_INVALID_REQUEST;
                }
                break;

            case re_first_major_digit:
                if (ch < '1' || ch > '9') {
                    return HTTP_PARSE_INVALID_REQUEST;
                }
                
                req->http_major = ch - '0';
                state = re_major_digit;
                break;
                
            case re_major_digit:
                if (ch == '.') {
                    state = re_first_minor_digit;
                    break;
                }
                
                if (ch < '0' || ch > '9') {
                    return HTTP_PARSE_INVALID_REQUEST;
                }
                
                req->http_major = req->http_major * 10 + ch - '0'; //not likely to happen
                break;
                
            case re_first_minor_digit:
                if (ch < '1' || ch > '9') {
                    return HTTP_PARSE_INVALID_REQUEST;
                }
                
                req->http_minor = ch - '0';
                state = re_minor_digit;
                break;
                
            case re_minor_digit:
                if (ch == CR) {
                    state = re_almost_done; // HTTP/1
                    break;
                }
                
                if (ch == LF) {
                    goto DONE;
                }
                
                if (ch == ' ') {
                    state = re_spaces_after_digit;
                    break;
                }
                
                if (ch < '0' || ch > '9') {
                    return HTTP_PARSE_INVALID_REQUEST;
                }
                
                req->http_minor = req->http_minor * 10 + ch - '0';
                break;
                
            case re_spaces_after_digit:
                switch (ch) {
                    case ' ':
                        break;
                    case CR:
                        state = re_almost_done;
                        break;
                    case LF:
                        goto DONE;
                    default:
                        return HTTP_PARSE_INVALID_REQUEST;
                }
                break;
            
            case re_almost_done:
                req->request_end = p - 1;
                switch (ch) {
                    case LF:
                        goto DONE;
                    default:
                        return HTTP_PARSE_INVALID_REQUEST;
                }
        }
    }
    
    req->pos = pi;
    req->state = state;
    
    return AGAIN;
    
DONE:
    req->pos = pi + 1;
    
    if (req->request_end == NULL) {
        req->request_end = p;
    }
    
    req->state = re_start;
    
    return OK;
}

int parse_request_body(request_t* req) {
    u_char ch, *p;
    size_t pi;
    
    enum {
        re_start = 0,
        re_key,// time
        re_spaces_before_colon,// colon = :
        re_spaces_after_colon,
        re_value,
        re_cr,
        re_crlf,
        re_crlfcr
    } state;
    
    state = req->state;
    CHECK(state == 0, "state should be 0");
    
    header_t* hd;
    
    for (pi = req->pos; pi < req->last; pi++) {
        p = (u_char*)&req->buf[pi % MAX_BUF];
        ch = *p;
        
        switch (state) {
            case re_start:
                if (ch == CR || ch == LF) {
                    break;
                }
                
                req->cur_header_key_start = p;//current header's key start
                state = re_key;
                break;
                
            case re_key:
                if (ch == ' ') {
                    req->cur_header_key_end = p;
                    state = re_spaces_before_colon;
                    break;
                }
                
                if (ch == ':') {
                    req->cur_header_key_end = p;
                    state = re_spaces_after_clon;
                    break;
                }
                break;

            case re_spaces_before_colon:
                if (ch == ' ') {
                    break;
                }
                else if (ch == ':') {
                    state = re_spaces_after_colon;
                    break;
                }
                else {
                    return ZV_HTTP_PARSE_INVALID_HEADER;
                }
                
            case re_spaces_after_colon:
                if (ch == ' ') {
                    break;
                }
                
                state = re_value;
                req->cur_header_value_start = p;
                break;
            
            case re_value:
                if (ch == CR) {
                    req->cur_header_value_end = p;
                    state = re_cr;
                }
                
                if (ch == LF) {
                    req->cur_header_value_end = p;
                    state = re_crlf;
                }
                break;
                
            case re_cr:
                if (ch == LF) {
                    state = re_crlf;
                    //save the current http header
                    hd = (header_t*)malloc(sizeof(struct header_t));
                    hd->key_start = req->cur_header_key_start;
                    hd->key_end = req->cur_header_key_end;
                    hd->value_start = req->cur_header_value_start;
                    hd->value_end = req->cur_header_value_end;
                    
                    list_add_head(&(hd->list), &(req->list));
                    
                    break;
                }
                else {
                    return ZV_HTTP_PARSE_INVALID_HEADER;
                }
                
            case re_crlf:
                if (ch == CR) {
                    state = re_crlfcr;
                }
                else {
                    req->cur_header_key_start = p;
                    state = re_key;
                }
                break;

            case re_crlfcr:
                switch (ch) {
                    case LF:
                        goto DONE;
                    default:
                        return ZV_HTTP_PARSE_INVALID_HEADER;
                }
                break;
        }
    }
    
    req->pos = pi;
    req->state = state;
    
DONE:
    req->pos = pi + 1;
    req->state = re_start;
    
    return OK;
}
