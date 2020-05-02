/*
 * Copyright (C) Lunar Eclipse
 * Copyright (C) https://github.com/xiaoqixian
 */

#include <stdint.h>
#include <getopt.h>
#include <signal.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "util.h"
#include "timeer.h"
#include "http.h"
#include "epoll.h"
#include "threadpool.h"

#define CONF "railgun.conf"
#define RAILGUN_VERSION "1.0"


