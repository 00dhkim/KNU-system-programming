#include "snake_lib.h"

int random_(int a, int b) {
	return (long long)rand()*(b - a + 1) / RAND_MAX + a;
}

// return 1: single, 2: multi
int print_home()
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
	puts("");

	int num;
	
	while(1) {
		puts("select menu");
		puts("1) start single game");
		puts("2) start multi game");
		puts("3) show score board");
		puts("4) game exit");
		putchar('>');
		scanf("%d", &num);
		getchar(); // '\n' 비우기

		switch(num) {
			case 1:
				return 1;
				break;

			case 2:
				return 2;
				break;

			case 3:
				show_scoreboard();
				break;

			case 4:
				puts("good bye");
				exit(0);

				break;
		}
	}

	puts("move: WASD, snake: @, food: &, wall: #\n");
	puts("press enter to start");
	while(getchar() != '\n'); // fflush(stdin);
}

// 지도 설정, 뱀 위치, 먹이 위치 랜덤 설정
// input: 1이면 single, 2이면 multi
void init_(int mode)
{
	srand((int)time(NULL));

	for (int i = 0; i <= MAP_SIZE; i++) {	//지도 설정
		map[0][i] = map[i][0] = map[MAP_SIZE][i] = map[i][MAP_SIZE] = wallNum;
	}	// ex) MAP_SIZE:100 -> 이동반경:1~99

	snake1[0].i = random_(1, MAP_SIZE-1);	//뱀 위치 설정
	snake1[0].j = random_(1, MAP_SIZE-1);
	map[snake1[0].i][snake1[0].j] = snake1Num;

	if(mode == 2) {
		snake2[0].i = random_(1, MAP_SIZE-1);
		snake2[0].j = random_(1, MAP_SIZE-1);
		map[snake2[0].i][snake2[0].j] = snake2Num;
	}

    set_food_posit();
}

void set_food_posit()
{
	do {
		food.i = random_(1, MAP_SIZE - 1);
		food.j = random_(1, MAP_SIZE - 1);

	} while (map[food.i][food.j] != emptyNum);

	map[food.i][food.j] = foodNum;
}

/**
 * getchar() and return direction number
 */
int input_direction()	//방향 입력후 리턴
{
	char direc;
	while(1) {
		direc = getchar();
		while(getchar() != '\n'); // '\n' 지우기

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
void what_is_direction(int direc, int user)
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
	if(user == 1) {
		if (map[snake1[0].i + di][snake1[0].j + dj] == wallNum || map[snake1[0].i + di][snake1[0].j + dj] == wallNum) {	// 이동할 부분이 벽 or 뱀 이라면
			death1 = 1;
		}
		else if (map[snake1[0].i + di][snake1[0].j + dj] == foodNum)
		{
			length1++;
			set_food_posit();
			grow = 1;
		}
	}
	else {
		if (map[snake2[0].i + di][snake2[0].j + dj] == wallNum || map[snake2[0].i + di][snake2[0].j + dj] == wallNum) {	// 이동할 부분이 벽 or 뱀 이라면
			death2 = 1;
		}
		else if (map[snake2[0].i + di][snake2[0].j + dj] == foodNum)
		{
			length2++;
			set_food_posit();
			grow = 1;
		}
	}
}

void move_(int user)	//snake1[]도 옮겨야 하고, map[][]의 뱀 정보도 옮겨야 함
{
	if(user == 1) {
		for (int i = length1-1; i >= 0; i--) {
			snake1[i + 1].i = snake1[i].i;
			snake1[i + 1].j = snake1[i].j;
		}
		snake1[0].i = snake1[1].i + di;
		snake1[0].j = snake1[1].j + dj;

		map[snake1[0].i][snake1[0].j] = snake1Num;
		
		if (!grow) {
			map[snake1[length1].i][snake1[length1].j] = emptyNum;
			snake1[length1].i = snake1[length1].j = emptyNum;
		}
	}
	else {
		for (int i = length2-1; i >= 0; i--) {
			snake2[i + 1].i = snake2[i].i;
			snake2[i + 1].j = snake2[i].j;
		}
		snake2[0].i = snake2[1].i + di;
		snake2[0].j = snake2[1].j + dj;

		map[snake2[0].i][snake2[0].j] = snake2Num;
		
		if (!grow) {
			map[snake2[length2].i][snake2[length2].j] = emptyNum;
			snake2[length2].i = snake2[length2].j = emptyNum;
		}
	}
}

void print_map(int mode)
{
	system("clear");
	for (int i = 0; i <= MAP_SIZE; i++) {
		for (int j = 0; j <= MAP_SIZE; j++) {
			if (map[i][j] == emptyNum) printf("- ");
			else if (map[i][j] == snake1Num) printf("@ ");
			else if (map[i][j] == snake2Num) printf("* ");
			else if (map[i][j] == foodNum) printf("& ");
			else if (map[i][j] == wallNum) printf("# ");
			else printf("%d ", map[i][j]);
		}
		printf("\n");
	}

	printf("\nsnake1 position: (%d, %d)\n", snake1[0].i, snake1[0].j);	//snake1 position
	if(mode == 2) printf(  "snake2 position: (%d, %d)\n", snake2[0].i, snake2[0].j);	//snake2 position
    printf(  "food   position: (%d, %d)\n", food.i, food.j);
	printf(  "  snake1 length: %d\n", length1);
	if(mode == 2) printf(  "  snake2 length: %d\n", length2);
}

void show_scoreboard() {
	
	FILE *fp = fopen("scoreboard.txt","r");
	
	int score;
	char name[200], datebuf[20], timebuf[20];

	puts("\n<< scoreboard >>\n");

	while(-1 != fscanf(fp, "%d%s%s%s", &score, name, datebuf, timebuf)) {
		printf("%3d %10s %s %s\n", score, name, datebuf, timebuf);
	}

	puts("\n==================\n");
	puts("press enter to continue");
	while(getchar() != '\n');
}

// 게임 실행을 담당
void single_main_function() {

	while (1) {
		alarm(5);
		print_map(1);

		di = dj = grow = 0;
		what_is_direction(input_direction(), 1);

		if (death1) { // 사망이면 종료
			return;
		}
		
		move_(1);
	}

	puts("you dead.");
}

// 프로그램 종료 처리
void program_exit(int mode) {

	signal(SIGINT, SIG_IGN); // Ctrl-C 눌러도 무시
	signal(SIGALRM, SIG_IGN); // 5초동안 아무것도 안해도 무시
	
	puts("\n######################\n");
	puts("GAME OVER, press enter\n");
	puts("######################\n");
	while(getchar() != '\n');
	system("clear");
	
	if(mode == 2) {

		if(death1) puts("player 2 is winner.");
		else puts("player 1 is winner.");

		printf("player 1's score: %d\n", length1);
		printf("player 1's score: %d\n", length2);

		puts("good bye");
		exit(0);
	}

	// mode == 1
	printf("your score: %d\n", length1);
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

	fprintf(fp, "%3d %20s %s\n", length1, name, timebuf);

	puts("register succeed");
	puts("good bye");
	exit(0);
}

