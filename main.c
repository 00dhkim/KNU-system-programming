#include <stdio.h>
#include <curses.h>

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

int main()
{
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


	return 0;
}
