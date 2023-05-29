#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
	char* word;
	int length;
	int repeat;
	struct List* next;
} List;


int compare_and_push(List* head, char leks[], List* element);
char* get_word(char temp[], char* line);
List* add(List* head, char leks[]);
void output(List* head);
List* find_word(List* head, List* element, List* word);
void create_copy(FILE* f, FILE* copy);
void read_file(FILE* copy);
char* get_word1(int begin, int* end, char temp[], char* word);
char* get_symbols(int begin, int* end, char temp[], char* word);
char* line_in_file(char* before, char* word, char* after, char* line);
void add_words(FILE* words, char* word1, char* word2, int counter);
void rewrite(int counter, char* word1, char* word2, FILE* copy1, FILE* copy2, FILE* words);
List* del_elements(List* head, List* word);
List* arhiv(List* head, FILE* copy1, FILE* copy2, FILE* words, int* number_of_file);
List* input(FILE* f, List* head);
