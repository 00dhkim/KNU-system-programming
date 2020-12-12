// 5초동안 아무 입력이 없으면 종료하는 프로그램
// 입력이 있으면 그 입력을 그대로 되돌려 줌 (echoing)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void wakeup(int signum) {
    puts("program end");
    exit(0);
}

int main() {

    puts("START");
    signal(SIGALRM, wakeup);
    alarm(5); // 5초 후 SIGALRM 발생

    char c;
    while(1) {
        c = getchar();
        putchar(c);
        alarm(5); // 남은 시간 다시 5로 설정
    }
    // NOTE: alarm(0) 하면 알람 종료

    return 0;
}