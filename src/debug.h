/*
 * FILE: debug.h
 * Copyright (C) LunarEclipse
 * 
 * Description:
 *   Some macros for debug are defined here
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#ifdef NO_DEBUG
#define DEBUG(M, ...)

#else
#define DEBUG(M, ...) fprintf(stderr, "DEBUG %s: %d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define CLEAN_ERRNO() (errno == 0 ? "None" : strerror(errno))

#define LOG_ERR(M, ...) fprintf(stderr, "[ERROR] (%s: %d: errno: %s)" M "\n", __FILE__, __LINE__, CLEAN_ERRNO(), ##__VA_ARGS__)

#define LOG_WARN(M, ...) fprintf(stderr, "[WARN] (%s: %d: errno: %s)" M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define LOG_INFO(M, ...) fprintf(stderr, "[INFO] (%s: %d)" M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define CHECK(A, M, ...) if (!(A)) { LOG_ERR(M "\n", ##__VA_ARGS__);} 

#define CHECK_EXIT(A, M, ...) if (!(A)) { LOG_ERR(M, "\n", ##__VA_ARGS__); exit(1);} 

#define CHECK_DEBUG(A, M, ...) if (!(A)) { DEBUG(M "\n", ##__VA_ARGS__);}

#endif
