#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <sys/wait.h>


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
void child_code() {	

	while (1) {
		print_map();

		di = dj = grow = 0;
		what_is_direction(input_direction());

		if (death) {	// 사망이면 종료
			exit(0);
		}
		
		move_();
	}
}

// 프로그램 전반 관리
void parent_code() {
	
	wait(0); // death
	
	puts("you dead.\nTHE END");
	printf("your score: %d\n", length);
	puts("register on the scoreboard.");
	puts("1) yes");
	puts("2) no");
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

	fprintf(fp, "%d %s\n", length, name);

	puts("register succeed");
	puts("good bye");
	exit(0);
}

int main() {

	print_home();
	init_();

	int pid = fork();

	switch(pid) {
		case -1:
			perror("fork");
			exit(1);
		case 0: // child
			child_code();
			break;
		default: // parent
			parent_code();
	}

	return 0;
}
