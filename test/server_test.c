// 클라이언트의 메시지를 단순히 매개만 하자
// 클라이언트는 두개 연결
// usage: ./server_test &

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <stdlib.h>

#define PORTNUM 13011
#define HOSTLEN 256
#define oops(msg) {perror(msg); exit(1);}

void child_procedure(int sock_id, int sock_fd) {

    if(sock_fd == -1) oops("accept");

    FILE *sock_fp = fdopen(sock_fd, "w");
    if(sock_fp == NULL) oops("fdopen");

    int i=10;
    while(i) {
        fprintf(sock_fp, "HELLO! this is server message %d\n", i--);
        fflush(sock_fp);
        printf("%d message sended to %d\n", i, sock_fp);
        sleep(1);
    }
    fprintf(sock_fp, "bye");

    fclose(sock_fp);
    printf("client %d closed\n", sock_fp);
}

int main(int argc, char *argv[]) {

    struct sockaddr_in saddr;
    struct hostent *hp;
    char hostname[HOSTLEN];
    int sock_id;
    int sock_fd;
    
    
    // step 1: ask kernel for a socket

    sock_id = socket(PF_INET, SOCK_STREAM, 0);
    if(sock_id == -1) {
        oops("socket");
    }

    // step 2: bind address to socket. address is host,port

    bzero( (void *)&saddr, sizeof(saddr));

    gethostname(hostname, HOSTLEN);
    hp = gethostbyname(hostname);

    bcopy( (void *)hp->h_addr_list[0], (void *)&saddr.sin_addr, hp->h_length);
    saddr.sin_port = htons(PORTNUM);
    saddr.sin_family = AF_INET;

    if( bind(sock_id, (struct sockaddr *)&saddr, sizeof(saddr)) != 0) {
        oops("bind");
    }
    
    // step 3: allow incoming calls with Qsize=1 on socket

    if(listen(sock_id, 1) != 0) {
        oops("listen");
    }

    // main procedure
    
    int pid;

    sock_fd = accept(sock_id, NULL, NULL);
    puts("client connected");
    
    pid = fork();

    switch(pid) {
        case -1:
            perror("fork");
            exit(1);
        
        case 0: // child
            child_procedure(sock_id, sock_fd);
            exit(0);
        
        //default:
            // pass
    }
    
}

