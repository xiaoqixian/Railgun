/*
 * FILE: rio.c
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Railgun
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "debug.h"
#include "rio.h"

//rio_readn - robustly read n bytes (unbuffered)
ssize_t rio_readn(int fd, void* buf, size_t n) {
    size_t nleft = n;
    ssize_t nread;
    char* bufp = (char*)buf;
    
    while (nleft > 0) {
        if ((nread = read(fd, bufp, nleft)) < 0) {
            if (errno == EINTR) //does not read anything because of interrupt signals
                nread = 0;
            else {
                LOG_ERR("errno = %d\n", errno);
                return -1;
            }
        }
        else if (nread == 0) {
            break;
        }
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);
}

ssize_t rio_writen(int fd, void* buf, size_t n) {
    size_t nleft = n;
    ssize_t nwrite;
    char* bufp = (char*)buf;
    
    while (nleft > 0) {
        if ((nwrite = write(fd, bufp, nleft)) <= 0) {
            if (errno = EINTR)
                nwrite = 0;
            else {
                LOG_ERR("errno = %d\n", errno);
                return -1;
            }
        }
        nleft -= nwrite;
        bufp += nwrite;
    }
    return n;
}

/*
 * rio_read - This is a wrapper for the Unix read() function that
 *   transfers min(n, rio_cnt) bytes from an internal buffer to a user
 *   buffer, where n is the number of bytes requested by the user and 
 *   rio_cnt is the number of unread bytes in the internal buffer. On
 *   entry, rio_read() refills the internal buffer via a call to 
 *   read() if the internal buffer is empty
 */

static ssize_t rio_read(rio_t* rp, char* buf, size_t n) {
    size_t cnt;
    
    while (rp->rio_cnt <= 0) {
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));
        if (rp->rio_cnt < 0) {
            if (errno == EAGAIN) {
                return -EAGAIN;
            }
            if (errno != EINTR) {
                return -1;
            }
        }
        else if (rp->rio_cnt == 0) {
            return 0;
        }
        else {
            rp->rio_bufptr = rp->rio_buf;
        }
    }
    
    //copy min(n, rp->rio_cnt) bytes from internal buffer to user buff
    cnt = n;
    if (rp->rio_cnt < (ssize_t)n) {
        cnt = rp->rio_cnt;
    }
    memcpy(buf, rp->rio_bufptr, cnt);
    rp->rio_cnt -= cnt;
    return cnt;
}

/*
 * rio_readinitb - Associate a descriptor with a read buffer and reset buffer
 */
void rio_init(rio_t* rp, int fd) {
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufptr = rp->rio_buf;
}

/*
 * rio_readnb - Robustly read n bytes to user buffer (bufferd)
 */
ssize_t rio_readnb(rio_t* rp, void* buf, size_t n) {
    size_t nleft = n;
    ssize_t nread;
    char* bufp = (char*)buf;
    
    while (nleft > 0) {
        if ((nread = rio_read(rp, bufp, nleft)) < 0) {
            if (errno == EINTR)
                nread = 0;
            else
                return -1;
        }
        else if (nread == 0)
            break;
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);
}

/*
 * rio_readlineb - robustly read a text line (bufferd)
 */
ssize_t rio_readlineb(rio_t* rp, void* buf, size_t maxlen) {
    size_t n;
    ssize_t rc;
    char c, *bufp = (char*)buf;
    
    for (n = 1; n < maxlen; n++) {
        if ((rc = rio_read(rp, &c, 1)) == 1) {
            *bufp++ = c;
            if (c == '\n') {
                break;
            }
        }
        else if (rc == 0) {
            if (n == 1) {
                //return and close fd
                return 0;
            }
            else {
                break;
            }
        }
        else if (rc == -EAGAIN) {
            //read next time
            return rc;
        }
        else {
            return -1;
        }
    }
    *bufp = 0;
    return n;
}
