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
extern void what_is_direction(int direc, int user);
extern void move_(int user);
extern void print_map(int mode, int user);
extern void single_main_function();
extern void program_exit(int mode);
extern void multi_main_function();

int mode; // 1: single, 2: multi

// Ctrl-C 입력 시 포기 선언
void give_up() {

	alarm(0);
	puts("You really want to give up?");
	puts("1) yes");
	puts("2) no");
	putchar('>');
	int num;
	scanf("%d", &num);
	if(num == 1) program_exit(mode);
	else print_map(mode, 0);
}

// 입력 시간 초과, program_exit() 호출하고 종료
void times_up() {
	
	puts("input times up");
	program_exit(mode);
	exit(0);
}

int main() {

	mode = print_home();

	init_(mode);
	signal(SIGINT, give_up);
	signal(SIGALRM, times_up);

	alarm(5); // 5초 후 SIGALRM 발생
	
	if(mode == 1) single_main_function();
	else multi_main_function();

	program_exit(mode);

	return 0;
}
