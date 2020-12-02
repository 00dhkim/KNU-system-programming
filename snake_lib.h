#ifndef SNAKE_LIB_H
#define SNAKE_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <conio.h>
//#include <io.h>
#include <fcntl.h>
#include <termio.h>
#include <curses.h>
#include <unistd.h>


#define MAP_SIZE 20
#define MAX_SNAKE_LENGTH 100

enum DirectionNumber {
    right = 0, left, down, up
};

int map[MAP_SIZE + 2][MAP_SIZE + 2] = { 0, };	// 빈공간: 0, 뱀: 1, 먹이: 2, 벽: 9
int snake_i[MAX_SNAKE_LENGTH + 2] = { 0, };	// 여기에 뱀의 각 부위의 i좌표 적을거임. snake_i[0]: 머리
int snake_j[MAX_SNAKE_LENGTH + 2] = { 0, };	// 뱀의 j좌표, snake_j[0]: 머리
int length = 1;	// 뱀의 길이, 먹이를 먹으면 +1
int death = 0;	// 0이면 생존, 1이면 사망
int grow = 0;	// 1이면 성장할 예정
int di, dj;
int food_i, food_j;

int random_(int a, int b);
void set_food_posit();
void print_home();
void init_();
void set_food_posit();
int input_direction();
void what_is_direction(int direc);
void move_();
void print_map();


#endif /* SNAKE_LIB_H */