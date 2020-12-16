// 서버에 연결하고, 서버에 클라 두개가 붙어서 연결 완료되면 시작
// 돌아가면서 말하는 프로그램 만들자 (끝말잇기 같은 느낌)
// usage: ./client_test `hostname` 13000

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#define oops(msg) {perror(msg); exit(1);}

int main(int argc, char *argv[]) {
    struct sockaddr_in servadd;
    struct hostent *hp;
    int sock_id, sock_fd;
    char message[BUFSIZ];
    int messlen;

    // step 1: get a socket

    sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_id == -1) oops("socket");

    // step 2: connect to server

    bzero(&servadd, sizeof(servadd));

    hp = gethostbyname(argv[1]);
    if(hp == NULL) oops(argv[1]);

    bcopy(hp->h_addr_list[0], (struct sockaddr *)&servadd.sin_addr, hp->h_length);

    servadd.sin_port = htons(atoi(argv[2]));
    servadd.sin_family = AF_INET;

    if(connect(sock_id, (struct sockaddr *)&servadd, sizeof(servadd)) != 0) {
        oops("connect");
    }
    puts("connection succeed");

    // step 3: main procedure

    FILE *sock_fp = fdopen(sock_fd, "w");

    while(1) {
        messlen = read(sock_id, message, BUFSIZ);
        if(messlen == -1) oops("read");        
        if(write(1, message, messlen) != messlen) oops("write");
        if(!strncmp(message, "bye", 3)) break;
    }
    close(sock_id);
    puts("\nended");

    return 0;
}
