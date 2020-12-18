#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CHILD_MESS "I want a cookie\n"
#define PAR_MESS "testing..\n"
#define oops(m,x) {perror(m); exit(x);}

int main() {
    int pipefd[2];
    int len;
    char buf[BUFSIZ];
    int read_len;

    if(pipe(pipefd) == -1) {
        oops("cannot get a pipe", 1);
    }

    char str[] = "100 1000";
    switch(fork()) {
        case -1:
            oops("cannot fork", 2);

        case 0: // child

            close(pipefd[0]); // 3번(in) close
            sleep(5);
            if(write(pipefd[1], str, strlen(str)) != strlen(str))
                oops("write", 3);

/*            len = strlen(CHILD_MESS);
            while (1) {
                if(write(pipefd[1], CHILD_MESS, len) != len)
                    oops("write", 3);
                sleep(5);
            }
*/
            puts("this is child");
            break;

        default: // parent

            close(pipefd[1]); // 4번(out) close

            
            read_len = read(pipefd[0], buf, BUFSIZ);
            int a,b;
            sscanf(buf, "%d %d", &a, &b);
            printf("%d\n", a+b);
            
/*            len = strlen(PAR_MESS);
            while(1) {
                if(write(pipefd[1], PAR_MESS, len) != len)
                    oops("write", 4);
                sleep(1);
                read_len = read(pipefd[0], buf, BUFSIZ);
                if(read_len <= 0) break;
                while(1, buf, read_len);
            }
*/          
            puts("this is parent");
            break;
    }

    return 0;
}
