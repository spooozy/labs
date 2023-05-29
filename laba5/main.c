#include "Header.h"

int main()
{
	int choice = 0;
	setlocale(LC_ALL, "Rus");
	struct Table* table;
	int size = 0;
	int task_choice = 3;
	table = (struct Table*)calloc(1, sizeof(struct Table));
	struct CASH* cash;
	cash = (struct CASH*)calloc(1, sizeof(struct CASH));
	cash->pointer = NULL;
	int k_size = 0;
	struct List* cname;
	cname = (struct List*)calloc(1, sizeof(struct List));
	cname->next = NULL;
	cname->prev = NULL;
	menu(choice, size, table, task_choice, cash, k_size, cname);
	return 0;
}
