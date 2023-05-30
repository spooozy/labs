#include "Header.h"

int check_counter(FILE* f, int counter, char check_line[], char temp)
{
	counter = 0;
	for (int i = 1;i < strlen(check_line);i++)
	{
		temp = fgetc(f);
		if (temp == check_line[i])
			counter++;
		else {
			counter = 0;
			return 0;
		}
	}
	return counter;
}

char* input_line(FILE* f)
{
	char* line = (char*)calloc(1, sizeof(char*));
	for (int i = 0;;i++)
	{
		line = (char*)realloc(line, (i + 1) * sizeof(char));
		line[i] = fgetc(f);
		if (line[i] == '<')
		{
			line[i] = '\0';
			break;
		}
	}
	return line;
}

struct Cameras* input_name_in_struct(FILE* f, struct Cameras* TOP, int j, int counter, char temp, char name_file[], char* line, int* elements)
{
	counter = check_counter(f, counter, name_file, temp);
	if (counter == strlen(name_file) - 1)
	{
		line = input_line(f);
		TOP = (struct Cameras*)realloc(TOP, (j + 1) * sizeof(struct Cameras));
		TOP[j].name = (char*)calloc(strlen(line) + 1, sizeof(char));
		strcpy(TOP[j].name, line);
		(*elements)++;
		free(line);
	}
	return TOP;
}

struct Cameras* input_format_in_struct(FILE* f, struct Cameras* TOP, int j, int counter, char temp, char format_file[], char* line, int* elements)
{
	counter = check_counter(f, counter, format_file, temp);
	if (counter == strlen(format_file) - 1)
	{
		line = input_line(f);
		TOP[j].format = (char*)calloc(strlen(line) + 1, sizeof(char));
		strcpy(TOP[j].format, line);
		(*elements)++;
		free(line);
	}
	return TOP;
}

struct Cameras* input_weight_in_struct(FILE* f, struct Cameras* TOP, int j, int counter, char temp, char weight_file[], char* line, int* elements)
{
	counter = check_counter(f, counter, weight_file, temp);
	if (counter == strlen(weight_file) - 1)
	{
		line = input_line(f);
		TOP[j].weight = (char*)calloc(strlen(line) + 1, sizeof(char));
		strcpy(TOP[j].weight, line);
		(*elements)++;
		free(line);
	}
	return TOP;
}

struct Cameras* input_dimensions_in_struct(FILE* f, struct Cameras* TOP, int j, int counter, char temp, char dimensions_file[], char* line, int* elements)
{
	counter = check_counter(f, counter, dimensions_file, temp);
	if (counter == strlen(dimensions_file) - 1)
	{
		line = input_line(f);
		TOP[j].dimensions = (char*)calloc(strlen(line) + 1, sizeof(char));
		strcpy(TOP[j].dimensions, line);
		(*elements)++;
		free(line);
	}
	return TOP;
}

struct Cameras* input_speed_in_struct(FILE* f, struct Cameras* TOP, int j, int counter, char temp, char speed_file[], char* line, int* elements)
{
	counter = check_counter(f, counter, speed_file, temp);
	if (counter == strlen(speed_file) - 1)
	{
		line = input_line(f);
		TOP[j].speed = (char*)calloc(strlen(line) + 1, sizeof(char));
		strcpy(TOP[j].speed, line);
		(*elements)++;
		free(line);
	}
	return TOP;
}

struct Cameras* input_buy_in_struct(FILE* f, struct Cameras* TOP, int j, int counter, char temp, char buy_file[], char* line, int* elements)
{
	counter = check_counter(f, counter, buy_file, temp);
	if (counter == strlen(buy_file) - 1)
	{
		line = input_line(f);
		TOP[j].buy = (char*)calloc(strlen(line) + 1, sizeof(char));
		strcpy(TOP[j].buy, line);
		(*elements)++;
		free(line);
	}
	return TOP;
}
struct Cameras* unput_in_top(struct Cameras* TOP)
{
	TOP[0].in_top = TOP1;
	TOP[1].in_top = TOP2;
	TOP[2].in_top = TOP3;
	TOP[3].in_top = TOP4;
	TOP[4].in_top = TOP5;
	TOP[5].in_top = TOP6;
	TOP[6].in_top = TOP7;
	return TOP;
}

struct Cameras* input(struct Cameras* TOP, FILE* f, char name_file[], char format_file[], char weight_file[], char dimensions_file[], char speed_file[], char buy_file[], int* cam_num)
{
	char temp;
	char* line;
	int counter = 0, j = 0, elements = 0;
	line = (char*)calloc(1, sizeof(char*));
	while (!feof(f))
	{
		temp = fgetc(f);
		if (temp == name_file[0])
			TOP = input_name_in_struct(f, TOP, j, counter, temp, name_file, line, &elements);

		if (temp == format_file[0])
			TOP = input_format_in_struct(f, TOP, j, counter, temp, format_file, line, &elements);

		if (temp == weight_file[0])
			TOP = input_weight_in_struct(f, TOP, j, counter, temp, weight_file, line, &elements);

		if (temp == dimensions_file[0])
			TOP = input_dimensions_in_struct(f, TOP, j, counter, temp, dimensions_file, line, &elements);

		if (temp == speed_file[0])
			TOP = input_speed_in_struct(f, TOP, j, counter, temp, speed_file, line, &elements);

		if (temp == buy_file[0])
			TOP = input_buy_in_struct(f, TOP, j, counter, temp, buy_file, line, &elements);

		if (elements == 6)
		{
			j++;
			elements = 0;
		}
	}
	(*cam_num) = j;
	TOP = unput_in_top(TOP);
	return TOP;
}

int check_choice(int res, int cam_num)
{
	char choice;
	char cam = cam_num + '0';
	scanf("%c", &choice);
	if (choice < '1' || choice > cam)
	{
		printf("try again\n");
		getchar();
		res = check_choice(res, cam_num);
	}
	else res = choice - '0';
	return res;
}

struct Cameras* del_camera(struct Cameras* TOP, int res, int *cam_num)
{
	for (int i = res - 1;i < (*cam_num);i++)
	{
		TOP[i] = TOP[i + 1];
	}
	(*cam_num)--;
	TOP = (struct Cameras*)realloc(TOP, (*cam_num) * sizeof(struct Cameras));
	return TOP;
}

void output(struct Cameras* TOP, int cam_num)
{
	printf("\nTOP -- Camera name ------ Format ----- Weight ---------- Dimensions --------------------------- Speed ------------------ Buy: $\n\n");
	for (int i = 0;i < cam_num;i++)
	{
		printf("%-5d", TOP[i].in_top);
		printf("%-20s", TOP[i].name);
		printf("%-10s", TOP[i].format);
		printf("%-18s", TOP[i].weight);
		printf("%-30s", TOP[i].dimensions);
		printf("%-40s", TOP[i].speed);
		printf("%-10s\n", TOP[i].buy);
	}
}

void sort_name(struct Cameras* TOP, int cam_num)
{
	int i, j, n;
	int gap, flg;
	struct Cameras temp;
	for (gap = cam_num / 2; gap > 0;gap /= 2)
		do {
			flg = 0;
			for (i = 0, j = gap;j < cam_num;i++, j++)
			{
				int compare = strcmp(TOP[i].name, TOP[j].name);
				if (compare > 0)
				{
					flg = 1;
					temp = TOP[i];
					TOP[i] = TOP[j];
					TOP[j] = temp;
				}
			}

		} while (flg);
}

void sort_buy(struct Cameras* TOP, int cam_num)
{
	int i, j, n;
	int gap, flg;
	struct Cameras temp;
	for (gap = cam_num / 2; gap > 0;gap /= 2)
		do {
			flg = 0;
			for (i = 0, j = gap;j < cam_num;i++, j++)
			{
				int compare = strcmp(TOP[i].buy, TOP[j].buy);
				if (compare > 0)
				{
					flg = 1;
					temp = TOP[i];
					TOP[i] = TOP[j];
					TOP[j] = temp;
				}
			}

		} while (flg);
}

void sort_speed(struct Cameras* TOP, int cam_num)
{
	int i, j, n;
	int gap, flg;
	struct Cameras temp;
	for (gap = cam_num / 2; gap > 0;gap /= 2)
		do {
			flg = 0;
			for (i = 0, j = gap;j < cam_num;i++, j++)
			{
				int compare = strcmp(TOP[i].speed, TOP[j].speed);
				if (compare < 0)
				{
					flg = 1;
					temp = TOP[i];
					TOP[i] = TOP[j];
					TOP[j] = temp;
				}
			}

		} while (flg);
}

void double_sort(struct Cameras* TOP, int cam_num)
{
	int i, j, n;
	int gap, flg;
	struct Cameras temp;
	for (gap = cam_num / 2; gap > 0;gap /= 2)
		do {
			flg = 0;
			for (i = 0, j = gap;j < cam_num;i++, j++)
			{
				int compare = strcmp(TOP[i].speed, TOP[j].speed);
				if (compare < 0)
				{
					flg = 1;
					temp = TOP[i];
					TOP[i] = TOP[j];
					TOP[j] = temp;
				}
				else if (compare == 0)
					if (strcmp(TOP[i].buy, TOP[j].buy) > 0)
					{
						flg = 1;
						temp = TOP[i];
						TOP[i] = TOP[j];
						TOP[j] = temp;
					}
			}
		} while (flg);
}

void menu(struct Cameras* TOP, int cam_num, int res)
{
	printf("\n---Enter\n 1 if you want to see the TOP\n 2 if you want to delete a camera\n 3 if you want to sort the TOP\n 4 if you want to sort by two fields\n 5 exit the program\n");
	int choice, sort_check;
	scanf_s("%d", &choice);
	printf("%d\n", choice);
	if (choice < 1 || choice > 5)
	{
		printf("---Wrong input. Try again\n");
		menu(TOP, cam_num, res);
	}
	switch (choice)
	{
	case 1:
		output(TOP, cam_num);
		menu(TOP, cam_num, res);
		break;
	case 2:
		getchar();
		printf("\n---Which camera do you want to delete?\n");
		res = check_choice(res, cam_num);
		TOP = del_camera(TOP, res, &cam_num);
		output(TOP, cam_num);
		menu(TOP, cam_num, res);
		break;
	case 3:
		printf("---Choose the field:\n--- 1 - Camera name\n--- 2 - Buy\n--- 3 - Speed\n");
		scanf("%d", &sort_check);
		if (sort_check < 1 || sort_check > 3)
		{
			getchar();
			printf("---Wrong input. Try again\n");
			menu(TOP, cam_num, res);
		}
		else if (sort_check == 1)
			sort_name(TOP, cam_num);
		else if (sort_check == 2)
			sort_buy(TOP, cam_num);
		else if (choice == 3)
			sort_speed(TOP, cam_num);
		output(TOP, cam_num);
		menu(TOP, cam_num, res);
		break;
	case 4:
		printf("---I suggest you sort the TOP by the fields 'Speed' and 'Buy'\n");
		double_sort(TOP, cam_num);
		output(TOP, cam_num);
		menu(TOP, cam_num, res);
		break;
	case 5:
		printf("Bye\n");
		break;
	}
}
