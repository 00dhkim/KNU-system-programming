#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <sys/wait.h>


extern int di;
extern int dj;
extern int grow;
extern int death;
extern int input_direction();
extern void print_home();
extern void init_();
extern void what_is_direction(int direc);
extern void move_();
extern void print_map();

// 게임 실행을 담당
void child_code() {	
	
	print_home();
	init_();

	while (1) {
		print_map();

		di = dj = grow = 0;
		what_is_direction(input_direction());

		if (death) {	// 사망이면 종료
			printf("death\n");
			break;
		}
		
		move_();
	}

	exit(0);
}

void parent_code() {
	
	wait(0);
	puts("THIS IS THE END");
}

int main() {

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
