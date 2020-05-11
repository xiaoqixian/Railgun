#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
    struct timeval tv;
    
    
    size_t cur = tv.tv_sec * 1000;
    printf("time = %zu\n", cur);
    
    sleep(2);
    gettimeofday(&tv, NULL);
    cur = tv.tv_sec * 1000;
    printf("time = %zu\n", cur);
    return 0;
}
