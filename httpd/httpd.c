/* httpd.c */

#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define LISTENADDR "0.0.0.0"

/* global */
char *error;

/* return 0 on error, else return a socket fd */
int srv_init(int portno) {
    int s;
    struct sockaddr_in srv;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if(s < 0) {
        error = "socket() error";
        return 0;
    }

    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = inet_addr(LISTENADDR);
    srv.sin_port = htons(portno);

    if(bind(s, (struct sockaddr *)&srv, sizeof(srv))) {
        close(s);
        error = "bind() error";
        return 0;
    }
}

int main(int argc, char *argv[]) {
    int s;
    char *port;

    if(argc < 2) {
        fprintf(stderr, "Usage: %s <listening port> \n", argv[0]);
        return -1;
    }
    else
        port = argv[1];


    s = srv_init(atoi(port));
}