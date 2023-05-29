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

int get_choice()
{
	printf("\n---Выберите действие:\n1)заполнить таблицу\n2)вывести таблицу\n3)найти интересующий элемент\n4)выход\n\n");
	char choice;
	choice = getchar();
	int temp = choice - '0';
	if (temp != 1 && temp != 2 && temp != 3 && temp != 4 && temp != 5 && temp != 6)
	{
		printf("\nОшибка ввода. Попрoбуйте снова\n");
		getchar();
		temp = get_choice();
	}
	else return temp;
}

int size_input()
{
	int size;
	printf("Введите размер таблицы:\n");
	scanf("%d", &size);
	if (size > MAX_SIZE)
	{
		printf("\nОшибка ввода. Попрoбуйте снова\n");
		size = size_input();
	}
	return size;
}


int get_el_key(char* line, int size)
{
	unsigned char source = line[0];
	for (int i = 1;i < strlen(line);i++)
		source += line[i];
	unsigned int temp_key = source - '0';
	temp_key = temp_key % size;
	return temp_key;
}

struct element* get_node(struct element* node, FILE* f, int size, int task_choice)
{
	if (f != EOF) {
		node->name = (char*)calloc(LEN_SIZE, sizeof(char));
		fscanf(f, "%s", node->name);
		node->type = (char*)calloc(LEN_SIZE, sizeof(char));
		fscanf(f, "%s", node->type);
		node->Id = (char*)calloc(LEN_SIZE, sizeof(char));
		fscanf(f, "%s", node->Id);
		if (task_choice == 1)
			node->key = get_el_key(node->name, size);
		else node->key = get_el_key(node->Id, size);
	}
	else return NULL;
	return node;
}

struct Table* fill_num(int size, struct Table* table)
{
	for (int i = 0;i < size;i++)
		table[i].list_size = 0;
	return table;
}

struct List* add_el_in_list(struct element* temp, struct List* head)
{
	struct List* temp_list = (struct List*)calloc(1, sizeof(struct List*));
	temp_list->prev = NULL;
	temp_list->next = head;
	temp_list->node = temp;
	temp_list->list_size_in_list = 2;
	head->prev = temp_list;
	return temp_list;
}

struct CASH* push(int num, struct CASH* head,struct Table* table)
{
	struct CASH* temp;
	temp = (struct CASH*)calloc(1, sizeof(struct CASH));
	temp->pointer = &table[num];
	temp->next = NULL;
	temp->prev = NULL;
	temp->key = table[num].elem_in_table->node->key;
	if (head->pointer == NULL)
	{
		return temp;
	}
	else {
		head->prev = temp;
		temp->next = head;
		return temp;
	}
}
int input_cash_size(int k_size, int size)
{
	printf("На какое кол-во элементов создать кэш?\n");
	scanf("%d", &k_size);
	if (k_size > size)
	{
		printf("\nОшибка ввода. Попрoбуйте снова\n");
		getchar();
		k_size = input_cash_size(k_size, size);
	}
	return k_size;
}

struct CASH* create_cash(struct CASH* cash, int size, struct Table* table)
{
	int i = 0;
	int j = 0;
	while (i < size)
	{
		if /*((table[j].list_size !=0) && (strcmp(table[j].elem_in_table->node->type, "A") == 0))*/ (table[j].list_size != 0) {
			cash = push(j, cash,table);
			i++;
		}
		j++;
	}
	return cash;
}


struct Table* input_table(int size, struct Table* table, FILE* f, int task_choice)
{
	int n;
	setlocale(LC_ALL, "Rus");
	table = fill_num(size, table);
	int i = 0, num = 0;
	struct element* temp;
	for (i = 0;i < size;i++)
	{
		temp = (struct element*)calloc(1, sizeof(struct element));
		temp = get_node(temp, f, size, task_choice);
		num = temp->key;
		if (table[num].list_size == 0)
		{
			table[num].elem_in_table = (struct List*)calloc(1, sizeof(struct List));
			table[num].list_size = 1;
			table[num].elem_in_table->list_size_in_list = 1;
			table[num].elem_in_table->next = NULL;
			table[num].elem_in_table->prev = NULL;
			table[num].elem_in_table->node = (struct element*)calloc(1, sizeof(struct element));
			table[num].elem_in_table->node = temp;
		}
		else
		{
			table[num].list_size++;
			table[num].elem_in_table = add_el_in_list(temp, table[num].elem_in_table);
		}
	}
	return table;
}

void output_table(struct Table* table, int size)
{
	printf("\n");
	for (int i = 0;i < size;i++)
	{
		if (table[i].list_size != 0)
		{
			struct List* temp = table[i].elem_in_table;
			while (temp != NULL)
			{
				printf("%-4d | %-10s | %-5s | %-15s\n", temp->node->key, temp->node->name, temp->node->type, temp->node->Id);
				temp = temp->next;
			}
		}
	}
}

void output_cash(struct CASH* head)
{
	struct CASH* temp = head;
	while (temp != NULL)
	{
		printf("%-5d | %-20s | %-20s\n", temp->key, temp->pointer->elem_in_table->node->name, temp->pointer->elem_in_table->node->Id);
		temp = temp->next;
	}
}

char* find_temp_ip(FILE* f, char temp_ip[LEN_SIZE], char IP[LEN_SIZE])
{
	char temp_line[LEN_SIZE];
	while (fscanf(f,"%s",temp_line)!=EOF)
		if (strcmp(IP, temp_line) == 0)
		{
			fscanf(f, "%s", temp_line);
			fscanf(f, "%s", temp_line);
			strcpy(temp_ip, temp_line);
			return temp_ip;
		}
	return temp_ip;
}

void find_el_in_cash(struct CASH* temp, char domain[LEN_SIZE], int **cash_flag,FILE *f)
{
	char temp_ip[LEN_SIZE];
	struct List* temp_list = (struct List*)calloc(1, sizeof(struct List));
	temp_list = temp->pointer->elem_in_table;
	while (temp_list != NULL)
	{
		if (strcmp(temp_list->node->name, domain) == 0)
		{
			if (strcmp(temp_list->node->type, "A") == 0)
				printf("---IP адрес: %s\n", temp_list->node->Id);
			else
			{
				strcpy(temp_ip, find_temp_ip(f, temp_ip, temp_list->node->Id));
				printf("---IP адрес: %s\n", temp_ip);
			}
			**cash_flag = 1;
		}
		temp_list = temp_list->next;
	}
}

void check_cash(struct CASH* cash, int* cash_flag, char domain[LEN_SIZE], int size, int domain_key,FILE *f)
{
	struct CASH* temp = (struct CASH*)calloc(1, sizeof(struct CASH));
	temp = cash;
	while (temp != NULL)
	{
		if (temp->key == domain_key)
		{
			find_el_in_cash(temp, domain, &cash_flag,f);
		}
		temp = temp->next;
	}
}

struct List* add_in_table(FILE* f, struct List* elem, char domain[LEN_SIZE], int domain_key, char temp_type[LEN_SIZE],char temp_ip[LEN_SIZE])
{
	elem->next = NULL;
	elem->prev = NULL;
	elem->list_size_in_list = 1;
	elem->node = (struct element*)calloc(1, sizeof(struct element));
	elem->node->Id = (char*)calloc(LEN_SIZE, sizeof(char));
	elem->node->name = (char*)calloc(LEN_SIZE, sizeof(char));
	elem->node->type = (char*)calloc(LEN_SIZE, sizeof(char));
	elem->node->key = domain_key;
	strcpy(elem->node->name, domain);
	strcpy(elem->node->Id, temp_ip);
	strcpy(elem->node->type, temp_type);
	return elem;
}

struct Table* search_in_file(char domain[LEN_SIZE], FILE* f, int *cash_flag,struct Table*table, int domain_key)
{
	char temp_line[LEN_SIZE];
	char temp_type[LEN_SIZE];
	char temp_ip[LEN_SIZE];
	while ((fscanf(f, "%s", temp_line) != EOF)&& (*cash_flag==0))
	{
		if (strcmp(temp_line, domain) == 0)
		{
			table[domain_key].list_size = 1;
			table[domain_key].elem_in_table = (struct List*)calloc(1, sizeof(struct List));
			fscanf(f, "%s", temp_type);
			fscanf(f, "%s", temp_ip);
			if (strcmp(temp_type, "A") == 0)
			{
				*cash_flag = 1;				
				table[domain_key].elem_in_table = add_in_table(f, table[domain_key].elem_in_table, domain, domain_key,temp_type,temp_ip);
			}
			else {
				fclose(f);
				if ((f = fopen("names.txt", "r")) == NULL)
				{
					printf("открыть исходный файл\n");
					exit(1);
				}
				while ((fscanf(f, "%s", temp_line) != EOF) && (*cash_flag == 0))
				{
					if (strcmp(temp_line, temp_ip) == 0)
					{
						*cash_flag = 1;
						fscanf(f, "%s", temp_type);
						strcpy(temp_type, "CNAME");
						fscanf(f, "%s", temp_ip);
						table[domain_key].elem_in_table = add_in_table(f, table[domain_key].elem_in_table, domain, domain_key, temp_type, temp_ip);
					}
				}
				fclose(f);
			}
			printf("---Элемент с доменным именем %s найден.\n---Его IP адрес:%s \n", table[domain_key].elem_in_table->node->name,table[domain_key].elem_in_table->node->Id);
		}
	}
	//fclose(f);
	return table;
}

struct CASH* change_cash(struct Table* table, struct CASH* cash, int domain_key)
{	
	struct CASH* head = (struct CASH*)calloc(1, sizeof(struct CASH));
	head->next = cash;
	head->prev = NULL;
	head->key = domain_key;
	head->pointer = &table[domain_key];
	struct CASH* temp = cash;
	while (temp->next != NULL)
		temp = temp->next;
	temp->prev->next = NULL;
	//free(temp->pointer);
	free(temp);
	return head;
}

int check_IP(char str[LEN_SIZE])
{
	int g = 0;
	int point = 0;
	int sum;
	int i = 0;
	for (int j = 0; j < strlen(str); j++) {
		if (str[j] == 46) { point++; }
	}
	if (point != 3) {
		g++;
		return g;
	}
	while (i < strlen(str)) {
		int k[4];
		sum = 0;
		for (int j = 0; j <= 3; j++) { k[j] = 0; }
		int j = 3;
		point = 0;
		while (str[i] != '.' && i < strlen(str)) {
			k[j] = str[i] - '0';
			j--;
			point++;
			i++;
		}
		if (point > 3) {
			g++;
			return g;
		}
		if (point == 1) { sum = k[3]; }
		if (point == 2) { sum = k[3] * 10 + k[2]; }
		if (point == 3) { sum = k[3] * 100 + k[2] * 10 + k[1]; }
		if (sum > 999 || sum < 0) {
			g++;
			return g;
		}
		i++;

	}
	return g;
}

FILE* write_in_file(FILE* f, FILE* new, char line[LEN_SIZE], int task_choice)
{
	char new_id[LEN_SIZE];
	char new_type[LEN_SIZE];
	char new_name[LEN_SIZE];
	int flag_ip = 1;
	printf("---Введите тип данных (А/CNAME)\n");
	scanf("%s", &new_type);
	if (task_choice == 1)
	{
		while (flag_ip == 1)
		{
			printf("Введите IP адрес\n");
			scanf("%s", &new_id);
			flag_ip = check_IP(new_id);
		}
	}
	else
	{
		printf("---Введите доменное имя\n");
		scanf("%s", &new_name);
	}
	char temp[LEN_SIZE];
	if (task_choice == 1)
	{
		fputs(line, new);
		fputc(' ', new);
		fputs(new_type, new);
		fputc(' ', new);
		fputs(new_id, new);
		fputc('\n', new);
	}
	else
	{
		fputs(new_name, new);
		fputc(' ', new);
		fputs(new_type, new);
		fputc(' ', new);
		fputs(line, new);
		fputc('\n', new);
	}
	int counter = 1;
	while (fscanf(f, "%s", temp) != EOF)
	{
		fputs(temp, new);
		if ((counter % 3 == 1) || (counter % 3 == 2))
			fputc(' ', new);
		else fputc('\n', new);
		counter++;
	}
	return new;
}

struct List* push_in_cname(struct List* head, struct element* node)
{
	struct List* temp = (struct List*)calloc(1, sizeof(struct List));
	temp->list_size_in_list = 0;
	temp->next = NULL;
	temp->prev = NULL;
	temp->node = (struct element*)calloc(1, sizeof(struct element));
	temp->node->key = node->key;
	temp->node->name = (char*)calloc(strlen(node->name), sizeof(char));
	strcpy(temp->node->name, node->name);
	temp->node->Id = (char*)calloc(strlen(node->Id), sizeof(char));
	strcpy(temp->node->Id, node->Id);
	temp->node->type = (char*)calloc(strlen(node->type), sizeof(char));
	strcpy(temp->node->type, node->type);
	if (head->node == NULL)
		head = temp;
	else
	{
		temp->next = head;
		head->prev = temp;
	}
	return temp;
}


int find_ip_in_table(struct Table* table, int ip_flag, char IP[LEN_SIZE], int size, struct List* cname)
{
	int temp_ip_ponter = get_el_key(IP, size);
	struct List* temp_find_ip = (struct List*)calloc(1, sizeof(struct List));
	temp_find_ip = table[temp_ip_ponter].elem_in_table;
	char temp_name_find_ip[LEN_SIZE];
	struct List* temp_cname = (struct List*)calloc(1, sizeof(struct List));
	temp_cname = cname;
	printf("\nДомены, соответсвующие введённому IP:\n");
	if (table[temp_ip_ponter].list_size == 0)
	{
		ip_flag = 1;
	}
	else {
		while (temp_find_ip != NULL)
		{
			if (strcmp(IP, temp_find_ip->node->Id) == 0)
			{
				printf("%s\n", temp_find_ip->node->name);
				ip_flag = 0;
				while (temp_cname != NULL)
				{
					if (strcmp(temp_cname->node->Id, temp_find_ip->node->name) == 0)
						printf("%s\n", temp_cname->node->name);
					temp_cname = temp_cname->next;
				}
			}
			temp_find_ip = temp_find_ip->next;
		}
	}
	if (ip_flag == 1)
	{
		printf("В таблице нет таких элементов\n");
	}
	return ip_flag;
}

struct List* input_cname(struct Table* table, int size, struct List* cname)
{
	struct List* temp = (struct List*)calloc(1, sizeof(struct List));
	for (int i = 0;i < size;i++)
	{
		if (table[i].list_size != 0)
		{
			if (table[i].list_size == 1)
			{
				if (strcmp(table[i].elem_in_table->node->type, "CNAME") == 0)
					cname = push_in_cname(cname, table[i].elem_in_table->node);
			}
			else
			{
				temp = table[i].elem_in_table;
				while (temp != NULL) {
					if (strcmp(temp->node->type, "CNAME") == 0)
						cname = push_in_cname(cname, temp->node);
					temp = temp->next;
				}
			}
		}
	}
	return cname;
}


void free_node(struct List* head)
{
	if (head->list_size_in_list == 1)
		free(head);
	else {
		struct List* node = head;
		while (node->next != NULL)
			node = node->next;
		struct List* temp = node;
		while (temp != NULL)
		{
			temp = temp->prev;
			free(temp->next);
		}
	}
}

void free_table(struct Table* table, int size)
{
	for (int i = 0;i < size;i++)
	{
		if (table[i].list_size != 0)
			free_node(table[i].elem_in_table);
	}
}


struct CASH* change_cash_fined(struct CASH* cash, char domain[])
{
	struct CASH* temp = cash;
	while (strcmp(temp->pointer->elem_in_table->node->name, domain) != 0)
		temp = temp->next;
	temp->prev->next = temp->next;
	temp->next = cash;
	return temp;
}
void menu(int choice, int size, struct Table* table, int task_choice, struct CASH* cash, int k_size, struct List* cname)
{
	char file[] = "names.txt";
	char temp_file[] = "new.txt";
	char del[] = "del.txt";
	FILE* f;
	FILE* new;
	int flag_ip = 1;
	int ip_flag = 1;
	int* flag = 0;
	int change_file = 0;
	int *cash_flag = 0;
	struct element* temp_add_in_cash;
	temp_add_in_cash = (struct element*)calloc(1, sizeof(struct element));	
	if (task_choice == 3) {
		printf("---Выберите задачу:\n1)найти IP\n2)найти домен\n");
		scanf("%d", &task_choice);
		getchar();
	}		
	choice = get_choice();
	if ((task_choice == 3) && (choice!=1))
	{
		printf("Необходимо заполнить таблицу\n");
		choice = 1;
	}
	printf("%d\n", choice);
	switch (choice)
	{
	case 1:
		{
		size = size_input();
		table = (struct Table*)calloc(size, sizeof(struct Table));
		if ((f = fopen("names.txt", "r")) == NULL)
		{
			printf("открыть исходный файл\n");
			exit(1);
		}
		table = input_table(size, table, f, task_choice);
		fclose(f);
		printf("\n---Hash-таблица заполнена. Выберите дальнейшее действие:\n");
		getchar();
		menu(choice, size, table, task_choice, cash, k_size, cname);
		break;
		}
	case 2:
		{
		output_table(table, size);
		printf("\n---Выберите дальнейшее действие:\n");
		getchar();
		menu(choice, size, table, task_choice, cash, k_size, cname);
		break;
		}
	case 3: 
		{
		if (task_choice == 1)
		{
			if (cash->pointer == NULL)
			{
				k_size = input_cash_size(k_size, size);
				cash = create_cash(cash, k_size, table);
				
			}
			output_cash(cash);
			printf("Введите доменное имя\n");
			char domain[LEN_SIZE];
			scanf("%s", &domain);
			int domain_key = get_el_key(domain, size);
			if ((f = fopen("names.txt", "r")) == NULL)
			{
				printf("открыть исходный файл\n");
				exit(1);
			}
			check_cash(cash, &cash_flag, domain, size, domain_key, f);
			fclose(f);
			if (cash_flag == 0)
			{
				if ((f = fopen("names.txt", "r")) == NULL)
				{
					printf("открыть исходный файл\n");
					exit(1);
				}
				printf("---Элемента с данным доменным именем нет в кэше\n");
				table = search_in_file(domain, f, &cash_flag, table, domain_key);
				fclose(f);
				if (cash_flag == 1)
				{
					cash = change_cash(table, cash, domain_key);
					output_cash(cash);
				}
				else {
					printf("---Элемента с введённым доменным именем нет в исходном файле.\n");
					if ((f = fopen("names.txt", "r")) == NULL)
					{
						printf("открыть исходный файл\n");
						exit(1);
					}
					if ((new = fopen("new.txt", "w")) == NULL)
					{
						printf("открыть исходный файл не удалось\n");
						exit(1);
					}
					new = write_in_file(f, new, domain, task_choice);
					printf("Элемент был добавлен в файл\n");
					change_file = 1;
					fclose(f);
					fclose(new);
					rename(file, del);
					rename(temp_file, file);
					remove(del);
				}
			}
			else {
				cash = change_cash_fined(cash, domain);
			}
			printf("\n---Продолжить работу с  IP адресами?\n1)Да\n2)Нет\n");
			scanf("%d", &task_choice);
			if (task_choice == 2)
			task_choice = 3;
			getchar();
			menu(choice, size, table, task_choice, cash, k_size, cname);
		}
		else
		{
			int flag_IP = 1;
			char IP[LEN_SIZE];
			cname = input_cname(table, size, cname);
			while (flag_IP == 1)
			{
				printf("Введите IP адрес\n");
				scanf("%s", &IP);
				flag_IP = check_IP(IP);
			}
			ip_flag = find_ip_in_table(table, ip_flag, IP, size, cname);
			if (ip_flag == 1)
			{
				if ((f = fopen("names.txt", "r")) == NULL)
				{
					printf("открыть исходный файл не удалось\n");
					exit(1);
				}
				if ((new = fopen("new.txt", "w")) == NULL)
				{
					printf("открыть исходный файл не удалось\n");
					exit(1);
				}
				new = write_in_file(f, new, IP, task_choice);
				printf("Элемент был добавлен в файл\n");
				getchar();
				fclose(f);
				fclose(new);
				rename(file, del);
				rename(temp_file, file);
				remove(del);
			}
		}
		printf("\n---Продолжить работу с доменными имeнами?\n1)Да\n2)Нет\n");
		scanf("%d", &task_choice);
		if (task_choice == 2)
		task_choice = 3;
		getchar();
		menu(choice, size, table, task_choice, cash, k_size, cname);
		break;
	}
	case 4:
		{
		free(table);
		exit(0);
		break;
		}
	}
}

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
