#include "Header.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	List* head;
	head = NULL;
	FILE* f;FILE* copy1;FILE* copy2;FILE* words;
	int *number_of_file = 0;
	int number;
	char name[] = "copy.txt";
	if ((copy1 = fopen("copy1.txt", "w")) == NULL)
	{
		printf("открыть файл не удалось\n");
		exit(1);
	}
	else {
		if ((f = fopen("file.txt", "r")) == NULL)
		{
			printf("открыть файл не удалось\n");
			exit(1);
		}
		create_copy(f, copy1);
		fclose(f);
	}

	if ((copy2 = fopen("copy2.txt", "w")) == NULL)
	{
		printf("открыть файл не удалось\n");
		exit(1);
	}
	else {
		if ((f = fopen("file.txt", "r")) == NULL)
		{
			printf("открыть файл не удалось\n");
			exit(1);
		}
		create_copy(f, copy2);
		fclose(f);
	}

	if ((f = fopen("file.txt", "r")) == NULL)
	{
		printf("открыть файл не удалось\n");
		exit(1);
	}

	if ((words = fopen("words.txt", "w")) == NULL)
	{
		printf("открыть файл не удалось\n");
		exit(1);
	}

	head = input(f, head);
	fclose(f);
	head = arhiv(head,copy1,copy2,words,&number_of_file);	
	fclose(words);
	number = number_of_file;
	if (number % 2 == 0)
	{		
		if (remove("copy2.txt")==0)
			printf("DONE");
		rename("copy1.txt","copy.txt");
	}
	else {
		if(remove("copy1.txt")==0)
			printf("DONE");
		rename("copy2.txt", "copy.txt");
	}
	return 0;
}
