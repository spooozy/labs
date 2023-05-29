#include "Header.h"

int main()
{
	FILE* f;
	FILE* copy1;
	List* head;
	FILE* copy2;
	head = NULL;
	int* number = 0;
	int number_of_file;
	if ((f = fopen("words.txt", "r")) == NULL)
	{
		printf("1 открыть файл words не удалось\n");
		exit(1);
	}
	head = input(f,head);
	fclose(f);
	if ((copy1 = fopen("copy.txt", "r")) == NULL)
	{
		printf("открыть файл copy не удалось\n");
		exit(1);
	}
	else if ((copy2 = fopen("copy1.txt", "w")) == NULL)
	{
		printf("открыть файл copy1 не удалось\n");
		exit(1);
	}
	else
	{
		create_copy(copy1, copy2);
		fclose(copy1);
	}
	head = rearhive(head, copy1, copy2,&number);
	number_of_file = number;
	if (number_of_file % 2 == 0)
	{
		if (remove("copy2.txt") == 0)
		{
			printf("DONE");
		}
		rename("copy1.txt", "copy.txt");
	}
	else {
		if (remove("copy1.txt") == 0)
		{
			printf("DONE");
		}
		rename("copy2.txt", "copy.txt");
	}
	return 0;
}
