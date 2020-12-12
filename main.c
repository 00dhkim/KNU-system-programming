#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <sys/wait.h>
#include <signal.h>


extern int di;
extern int dj;
extern int grow;
extern int death;
extern int length;
extern int input_direction();
extern void print_home();
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

// 프로그램 전반 관리
void program_exit() {
	
	puts("GAME OVER, press enter");
	getchar();
	system("clear");
	printf("your score: %d\n", length);
	puts("register on the scoreboard.");
	puts("1) yes");
	puts("2) no");
	int num;
	scanf("%d", &num);
	
	if(num != 1) {
		puts("good bye");
		return;
	}

	// register on the scoreboard
	FILE *fp = fopen("scoreboard.txt","a");
	puts("input your name");
	char name[100];
	scanf("%s", name);

	fprintf(fp, "%d %s\n", length, name);

	puts("register succeed");
	puts("good bye");
	return;
}

// Ctrl-C 입력 시 포기 선언
void give_up(int signum) {

	puts("You really want to give up?");
	puts("1) yes");
	puts("2) no");
	int num;
	scanf("%d", &num);
	if(num == 1) program_exit();
}

// 입력 시간 초과, program_exit() 호출하고 종료
void times_up(int signum) {
	
	puts("input times up");
	program_exit();
	exit(0);
}

int main() {

	signal(SIGINT, give_up);
	signal(SIGALRM, times_up);

	print_home();
	init_();

	alarm(5); // 5초 후 SIGALRM 발생
	main_loop();

	program_exit();

	return 0;
}
