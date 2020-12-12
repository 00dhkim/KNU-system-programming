#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>


extern int di;
extern int dj;
extern int grow;
extern int death;
extern int length;
extern int input_direction();
extern int print_home();
extern void init_();
extern void what_is_direction(int direc);
extern void move_();
extern void print_map();

// 게임 실행을 담당
void main_loop() {

	while (1) {
		alarm(5);
		print_map();

		di = dj = grow = 0;
		what_is_direction(input_direction());

		if (death) { // 사망이면 종료
			return;
		}
		
		move_();
	}

	puts("you dead.");
}

// 프로그램 종료 처리
void program_exit() {

	signal(SIGINT, SIG_IGN); // Ctrl-C 눌러도 무시
	signal(SIGALRM, SIG_IGN); // 5초동안 아무것도 안해도 무시
	
	puts("GAME OVER, press enter");
	while(getchar() != '\n');
	system("clear");
	printf("your score: %d\n", length);
	puts("register on the scoreboard.");
	puts("1) yes");
	puts("2) no");
	putchar('>');
	int num;
	scanf("%d", &num);
	
	if(num != 1) {
		puts("good bye");
		exit(0);
	}

	// register on the scoreboard
	FILE *fp = fopen("scoreboard.txt","a");
	puts("input your name");
	char name[100];
	scanf("%s", name);

	// time
	char timebuf[30];
	time_t t = time(NULL);
	struct tm* tm_info = localtime(&t);
	strftime(timebuf, 30, "%Y-%m-%d %H:%M ", tm_info);

	fprintf(fp, "%3d %20s %s\n", length, name, timebuf);

	puts("register succeed");
	puts("good bye");
	exit(0);
}

// Ctrl-C 입력 시 포기 선언
void give_up(int signum) {

	alarm(0);
	puts("You really want to give up?");
	puts("1) yes");
	puts("2) no");
	putchar('>');
	int num;
	scanf("%d", &num);
	if(num == 1) program_exit();
	else print_map();
}

// 입력 시간 초과, program_exit() 호출하고 종료
void times_up(int signum) {
	
	puts("input times up");
	program_exit();
	exit(0);
}

int main() {

	int mode; // 1: single, 2: multi
	
	mode = print_home();

	if(mode == 2) {
		puts("multi mode is not implemented");
		exit(0);
	}

	init_();
	signal(SIGINT, give_up);
	signal(SIGALRM, times_up);

	alarm(5); // 5초 후 SIGALRM 발생
	main_loop();

	program_exit();

	return 0;
}
