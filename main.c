/**
 * @file main.c
 * @author Dohyun Kim (00dh.kim@gmail.com)
 * @brief main source code for snake project
 * @version 0.1
 * @date 2020-12-18
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

// snake_lib.c의 함수를 사용하기 위해 extern으로 끌어옴
extern void init_(int mode);
extern int print_home();
extern void print_map(int mode, int user);
extern void single_main_function();
extern void multi_main_function();
extern void program_exit(int mode);

int mode; // 1: single, 2: multi

// Ctrl-C 입력 시 포기 선언
void give_up() {

	alarm(0); // alarm 종료
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
	signal(SIGINT, give_up); // REQ: 필수3
	signal(SIGALRM, times_up); // REQ: 필수2

	alarm(5); // REQ: 필수2, 5초 후 SIGALRM 발생
	
	if(mode == 1) single_main_function();
	else multi_main_function();

	program_exit(mode);

	return 0;
}
