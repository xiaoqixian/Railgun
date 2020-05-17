#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <netinet/in.h>

#define PORT 9090
#define BACKLOG 2
#define BUFFER 1024

/*
 * server's working process
 * 1.create a socket descriptor and a sockaddr type address
 * 2.bind this socket descriptor with the address
 *   bind(socket descriptor, sockaddr, sizeof(sockaddr))
 * 3.listen the server listening to the socket descriptor, you need to set the lengt of the listen queue
 * 4.when listening to the socket, we need to save the address from client into a sockaddr type pointer
 * 5.then the connection is set up
 */
void sig_process(int signal);
void sig_pipe(int signal);
void process_conn_server(int);

int main(int argc, char* argv[]) {
   int ss, sc, res; 
   struct sockaddr_in server_addr, client_addr;
   
   signal(SIGPIPE, sig_pipe);
   signal(SIGINT, sig_process);

   ss = socket(AF_INET, SOCK_STREAM, 0);
   bzero(&server_addr, sizeof(struct sockaddr_in));
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(PORT);
   server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

   res = bind(ss, (struct sockaddr*)&server_addr, sizeof(server_addr));
   if (res < 0) {
       printf("bind error\n");
       return -1;
   }
   
   res = listen(ss, BACKLOG);
   if (res < 0) {
       printf("listen error\n");
       return -1;
   }
   
   socklen_t addrlen = sizeof(struct sockaddr*);
   for (;;) {
       sc = accept(ss, (struct sockaddr*)&client_addr, &addrlen);
       if (sc < 0) {
           continue;
       }
       pid_t pid = fork();
       if (pid == 0) {
           process_conn_server(sc);
           close(ss);
       }
       else {
           close(sc);
       }
   }
}

static int ret_val = 0;

void *read_from_screen(void *arg) {
    int *sc = arg, res = 0;
    ssize_t size = 0;
    char buffer[BUFFER];
    for (;;) {
        size = read(0, buffer, BUFFER);
        if (size > 0) {
            send(*sc, buffer, size, 0);
        }
    }
}

void process_conn_server(int sc) {
    ssize_t size = 0;
    char buffer[BUFFER];
    char* str = "client: ";
    pthread_t pt;
    
    int res = pthread_create(&pt, NULL, (void*)read_from_screen, &sc);
    if (res < 0) {
        printf("create thread error\n");
        return ;
    }

    for (;;) {
        size = recv(sc, buffer, BUFFER, 0);
        if (size == 0) {
            return ;
        }
        write(1, str, strlen(str));
        write(1, buffer, size);
    }
}

void sig_process(int signal) {
    printf("catch exit signal\n");
    exit(0);
}

void sig_pipe(int signal) {
    printf("A client connect broke\n");
}
