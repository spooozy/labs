#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

enum Place {
	TOP1 = 1, TOP2, TOP3, TOP4, TOP5, TOP6, TOP7
};
struct Cameras {
	char* name;
	char* format;
	char* weight;
	char* dimensions;
	char* speed;
	char* buy;
	enum Place in_top;
};

int check_counter(FILE* f, int counter, char check_line[], char temp);
char* input_line(FILE* f);
struct Cameras* input_name_in_struct(FILE* f, struct Cameras* TOP, int j, int counter, char temp, char name_file[], char* line, int* elements);
struct Cameras* input_format_in_struct(FILE* f, struct Cameras* TOP, int j, int counter, char temp, char format_file[], char* line, int* elements);
struct Cameras* input_weight_in_struct(FILE* f, struct Cameras* TOP, int j, int counter, char temp, char weight_file[], char* line, int* elements);
struct Cameras* input_dimensions_in_struct(FILE* f, struct Cameras* TOP, int j, int counter, char temp, char dimensions_file[], char* line, int* elements);
struct Cameras* input_speed_in_struct(FILE* f, struct Cameras* TOP, int j, int counter, char temp, char speed_file[], char* line, int* elements);
struct Cameras* input_buy_in_struct(FILE* f, struct Cameras* TOP, int j, int counter, char temp, char buy_file[], char* line, int* elements);
struct Cameras* unput_in_top(struct Cameras* TOP);
struct Cameras* input(struct Cameras* TOP, FILE* f, char name_file[], char format_file[], char weight_file[], char dimensions_file[], char speed_file[], char buy_file[], int* cam_num);
int check_choice(int res, int cam_num);
struct Cameras* del_camera(struct Cameras* TOP, int res, int cam_num);
void output(struct Cameras* TOP, int cam_num);
void sort_name(struct Cameras* TOP, int cam_num);
void sort_speed(struct Cameras* TOP, int cam_num);
void double_sort(struct Cameras* TOP, int cam_num);
void menu(struct Cameras* TOP, int cam_num, int res);


