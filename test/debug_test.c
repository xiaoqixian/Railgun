#include "../src/debug.h"

int main() {
    //test DEBUG()
    int a = 1;
    //DEBUG("a = %d", a);
    
    //test LOG_ERR()
    errno = 23;
    LOG_ERR("wrong  %s", errno);
    //LOG_WARN();
    //LOG_INFO();
    
    return 0;
}
