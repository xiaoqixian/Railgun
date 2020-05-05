/*
 * FILE: http.h
 * Copyright (C) Lunar Eclipse
 */

#ifndef HTTP_H
#define HTTP_H

#include <strings.h>
#include <stdint.h>
#include "rio.h"
#include "list.h"
#include "debug.h"
#include "util.h"
#include "http_request.h"

#define MAXLINE 8192
#define SHORTLINE 512

#define STR3_CMP(m, c0, c1, c2, c3)\
    *(uint32_t*) m == ((c3 << 24) | (c2 << 16) | (c3 << 8) | c0)


typedef struct mine_type_s {
    const char* type;
    cosnr char* value;
} mine_type_t;

void do_request(void* infd);

#endif
