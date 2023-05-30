#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
	char* word;
	struct List* next;
} List;

List* add(List* head, char temp[]);
List* input(FILE* f, List* head);
void output(List* head);
void create_copy(FILE* f, FILE* copy);
char* get_symbols_before(int begin, int* end, char temp[], char* word);
char* get_symbols_after(int begin, int* end, char temp[], char* word);
char* get_word1(int begin, int* end, char temp[], char* word);
char* line_in_file(char* before, char* word, char* after, char* line);
void rewrite(int counter, char* word1, char* word2, FILE* copy1, FILE* copy2);
List* del_elements(List* head);
List* rearhive(List* head, FILE* copy1, FILE* copy2, int* number);
