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
			return;
		}
		
		move_();
	}
}

// 프로그램 전반 관리
void parent_code() {
	
	puts("you dead.\nTHE END");
	getchar();
	system("clear");
	printf("your score: %d\n", length);
	puts("register on the scoreboard.");
	puts("1) yes");
	puts("2) no");
	int num;
	char c;
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


int main() {

	print_home();
	init_();

	child_code();

	parent_code();

	return 0;
}
