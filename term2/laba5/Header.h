#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_SIZE 40
#define LEN_SIZE 40

struct element {
	char* name;
	char* Id;
	char* type;
	int key;
};

struct List {
	struct element* node;
	struct List* next;
	struct List* prev;
	int list_size_in_list;
};

struct Table {
	int list_size;
	struct List* elem_in_table;
};

struct CASH {
	int key;
	struct Table* pointer;
	struct CASH* next;
	struct CASH* prev;
};


int get_choice();
int get_el_key(char* line, int size);
struct element* get_node(struct element* node, FILE* f, int size, int task_choice);
struct Table* fill_num(int size, struct Table* table);
struct List* add_el_in_list(struct element* temp, struct List* head);
struct CASH* push(int num, struct CASH* head, struct Table* table);
int input_cash_size(int k_size, int size);
struct CASH* create_cash(struct CASH* cash, int size, struct Table* table);
struct Table* input_table(int size, struct Table* table, FILE* f, int task_choice);
void output_table(struct Table* table, int size);
void output_cash(struct CASH* head);
char* find_temp_ip(FILE* f, char temp_ip[LEN_SIZE], char IP[LEN_SIZE]);
void find_el_in_cash(struct CASH* temp, char domain[LEN_SIZE], int** cash_flag, FILE* f);
void check_cash(struct CASH* cash, int* cash_flag, char domain[LEN_SIZE], int size, int domain_key, FILE* f);
struct List* add_in_table(FILE* f, struct List* elem, char domain[LEN_SIZE], int domain_key, char temp_type[LEN_SIZE], char temp_ip[LEN_SIZE]);
struct Table* search_in_file(char domain[LEN_SIZE], FILE* f, int* cash_flag, struct Table* table, int domain_key);
struct CASH* change_cash(struct Table* table, struct CASH* cash, int domain_key);
int check_IP(char str[LEN_SIZE]);
FILE* write_in_file(FILE* f, FILE* new, char line[LEN_SIZE], int task_choice);
int find_ip_in_table(struct Table* table, int ip_flag, char IP[LEN_SIZE], int size, struct List* cname);
struct List* input_cname(struct Table* table, int size, struct List* cname);
void free_node(struct List* head);
void free_table(struct Table* table, int size);
struct CASH* change_cash_fined(struct CASH* cash, char domain[]);
void menu(int choice, int size, struct Table* table, int task_choice, struct CASH* cash, int k_size, struct List* cname);
