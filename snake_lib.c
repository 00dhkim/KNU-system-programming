#include "snake_lib.h"


int random_(int a, int b) {
	return (long long)rand()*(b - a + 1) / RAND_MAX + a;
}

void print_home()
{
	char logo[] = 
"          _____                    _____                    _____                    _____                    _____          \n\
         /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\         \n\
        /::\\    \\                /::\\____\\                /::\\    \\                /::\\____\\                /::\\    \\        \n\
       /::::\\    \\              /::::|   |               /::::\\    \\              /:::/    /               /::::\\    \\       \n\
      /::::::\\    \\            /:::::|   |              /::::::\\    \\            /:::/    /               /::::::\\    \\      \n\
     /:::/\\:::\\    \\          /::::::|   |             /:::/\\:::\\    \\          /:::/    /               /:::/\\:::\\    \\     \n\
    /:::/__\\:::\\    \\        /:::/|::|   |            /:::/__\\:::\\    \\        /:::/____/               /:::/__\\:::\\    \\    \n\
    \\:::\\   \\:::\\    \\      /:::/ |::|   |           /::::\\   \\:::\\    \\      /::::\\    \\              /::::\\   \\:::\\    \\   \n\
  ___\\:::\\   \\:::\\    \\    /:::/  |::|   | _____    /::::::\\   \\:::\\    \\    /::::::\\____\\________    /::::::\\   \\:::\\    \\  \n\
 /\\   \\:::\\   \\:::\\    \\  /:::/   |::|   |/\\    \\  /:::/\\:::\\   \\:::\\    \\  /:::/\\:::::::::::\\    \\  /:::/\\:::\\   \\:::\\    \\ \n\
/::\\   \\:::\\   \\:::\\____\\/:: /    |::|   /::\\____\\/:::/  \\:::\\   \\:::\\____\\/:::/  |:::::::::::\\____\\/:::/__\\:::\\   \\:::\\____\\\n\
\\:::\\   \\:::\\   \\::/    /\\::/    /|::|  /:::/    /\\::/    \\:::\\  /:::/    /\\::/   |::|~~~|~~~~~     \\:::\\   \\:::\\   \\::/    /\n\
 \\:::\\   \\:::\\   \\/____/  \\/____/ |::| /:::/    /  \\/____/ \\:::\\/:::/    /  \\/____|::|   |           \\:::\\   \\:::\\   \\/____/ \n\
  \\:::\\   \\:::\\    \\              |::|/:::/    /            \\::::::/    /         |::|   |            \\:::\\   \\:::\\    \\     \n\
   \\:::\\   \\:::\\____\\             |::::::/    /              \\::::/    /          |::|   |             \\:::\\   \\:::\\____\\    \n\
    \\:::\\  /:::/    /             |:::::/    /               /:::/    /           |::|   |              \\:::\\   \\::/    /    \n\
     \\:::\\/:::/    /              |::::/    /               /:::/    /            |::|   |               \\:::\\   \\/____/     \n\
      \\::::::/    /               /:::/    /               /:::/    /             |::|   |                \\:::\\    \\         \n\
       \\::::/    /               /:::/    /               /:::/    /              \\::|   |                 \\:::\\____\\        \n\
        \\::/    /                \\::/    /                \\::/    /                \\:|   |                  \\::/    /        \n\
         \\/____/                  \\/____/                  \\/____/                  \\|___|                   \\/____/         \n\
                                                                                                                             ";
	
	puts(logo);

	puts("===============================================================================");
	puts("move: WASD, snake: @, food: &, wall: #\n");
	puts("press enter to start");
	getchar();
}

void init_()	// 지도 설정, 뱀 위치, 먹이 위치 랜덤 설정
{
	srand((int)time(NULL));

	for (int i = 0; i <= MAP_SIZE; i++) {	//지도 설정
		map[0][i] = map[i][0] = map[MAP_SIZE][i] = map[i][MAP_SIZE] = 9;
	}	// ex) MAP_SIZE:100 -> 이동반경:1~99

	snake[0].i = random_(1, MAP_SIZE-1);	//뱀 위치 설정
	snake[0].j = random_(1, MAP_SIZE-1);
	map[snake[0].i][snake[0].j] = 1;

    set_food_posit();
}

void set_food_posit()
{
	do {
		food.i = random_(1, MAP_SIZE - 1);
		food.j = random_(1, MAP_SIZE - 1);

	} while (map[food.i][food.j] != 0);

	map[food.i][food.j] = 2;
}

/**
 * getchar() and return direction number
 */
int input_direction()	//방향 입력후 리턴
{
	char direc;
	while(1) {
		direc = getchar();

		switch (direc)
		{
		case 'w':
			return up;
		case 'a':
			return left;
		case 's':
			return down;
		case 'd':
			return right;
		default:
			printf("input error\n");
		}
	}
}

/**
 * direction number를 해석하고, di와 dj를 설정
 */
void what_is_direction(int direc)
{
	switch (direc)
	{
	case right:
		dj++;
		break;
	case left:
		dj--;
		break;
	case down:
		di++;
		break;
	case up:
		di--;
		break;
	}

	if (map[snake[0].i + di][snake[0].j + dj] == 9 || map[snake[0].i + di][snake[0].j + dj] == 1) {	// 이동할 부분이 벽 or 뱀 이라면
		death = 1;
	}
	else if (map[snake[0].i + di][snake[0].j + dj] == 2)
	{
		length++;
		set_food_posit();
		grow = 1;
	}
}

void move_()	//snake[]도 옮겨야 하고, map[][]의 뱀 정보도 옮겨야 함
{
	for (int i = length-1; i >= 0; i--) {
		snake[i + 1].i = snake[i].i;
		snake[i + 1].j = snake[i].j;
	}
	snake[0].i = snake[1].i + di;
	snake[0].j = snake[1].j + dj;

	map[snake[0].i][snake[0].j] = 1;
	
	if (!grow) {
		map[snake[length].i][snake[length].j] = 0;
		snake[length].i = snake[length].j = 0;
	}
}

void print_map()
{
	system("clear");
	for (int i = 0; i <= MAP_SIZE; i++) {
		for (int j = 0; j <= MAP_SIZE; j++) {
			if (map[i][j] == 0) printf("- ");
			else if (map[i][j] == 1) printf("@ ");
			else if (map[i][j] == 2) printf("& ");
			else if (map[i][j] == 9) printf("# ");
			else printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\nsnake position: (%d, %d)\n", snake[0].i, snake[0].j);	//snake position
    printf(  "food  position: (%d, %d)\n", food.i, food.j);
	printf("snake length: %d\n", length);
}

