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
extern void init_(int mode);
extern void what_is_direction(int direc);
extern void move_();
extern void print_map();
extern void single_main_function();
extern void program_exit();

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

	init_(mode);
	signal(SIGINT, give_up);
	signal(SIGALRM, times_up);

	alarm(5); // 5초 후 SIGALRM 발생
	
	single_main_function();

	program_exit();

	return 0;
}
