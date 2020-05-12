/*
 * FILE: http_parse.h
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Railgun
 */

#ifndef HTTP_PARSE_H
#define HTTP_PARSE_H

#define CR '\r'
#define LF '\n'
#define CRLFCRLF "\r\n\r\n"

int parse_request_line(request_t* req);
int parse_request_body(request_t* req);

#endif
