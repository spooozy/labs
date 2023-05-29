#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "locale.h"
#include <string.h>
# define SIZE 255

typedef struct {
	struct Tree* left;
	struct Tree* right;
	char number;
	char* data;
} Tree;

char* get_line(char temp[], char* line);
Tree* get_node(char temp_line[], Tree* node);
int input_choice(int choice);
Tree* input(FILE* f, Tree* node);
Tree* output(Tree* node);
Tree* input_add(Tree* node, char* line, char num);
Tree* add_node(Tree* node, char* yes, char* no);
void help(Tree* node, int* flag);
Tree* write_in_file(FILE** f, Tree* node);
