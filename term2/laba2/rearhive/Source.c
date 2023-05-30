#include "Header.h"
List* add(List* head, char temp[])
{
	List* element;
	element = (List*)calloc(1, sizeof(List));
	element->next = NULL;
	element->word = (char*)calloc(strlen(temp), sizeof(char));
	strcpy(element->word, temp);
	if (head == NULL)
		head = element;
	else {
		element->next = head;
		head = element;
	}
	return head;
}

List* input(FILE* f, List* head)
{
	char temp[35];
	while (!feof(f))
	{
		if (fscanf(f, "%s", temp) == EOF) break;
		else head = add(head, temp);
	}
	return head;
}

void output(List* head)
{
	printf("\n");
	List* out = head;
	while (out != NULL)
	{
		printf("%s\n", out->word);
		out = out->next;
	}
}

void create_copy(FILE* f, FILE* copy)
{
	char temp_1[256];
	while (fgets(temp_1, 255, f) != NULL)
		fputs(temp_1, copy);
	fclose(copy);
}

char* get_symbols_before(int begin, int* end, char temp[], char* word)
{
	int len = 0;
	int i = begin;
	while (i < strlen(temp))
	{
		if ((temp[i] >= 'A' && temp[i] <= 'Z') || (temp[i] >= 'a' && temp[i] <= 'z') || (temp[i] >= '0' && temp[i] <= '9'))
			break;
		{
			word = (char*)realloc(word, (len + 1) * sizeof(char));
			word[len] = temp[i];
			i++;
			len++;
		}
	}
	word = (char*)realloc(word, (len + 1) * sizeof(char));
	word[len] = '\0';
	*end = len;
	return word;
}

char* get_symbols_after(int begin, int* end, char temp[], char* word)
{
	int len = 0;
	int i = begin;
	while (i < strlen(temp))
	{
		if ((temp[i] >= 'A' && temp[i] <= 'Z') || (temp[i] >= 'a' && temp[i] <= 'z') || (temp[i] >= '0' && temp[i] <= '9'))
			break;
		{
			word = (char*)realloc(word, (len + 1) * sizeof(char));
			word[len] = temp[i];
			i++;
			len++;
		}
	}
	word = (char*)realloc(word, (len + 1) * sizeof(char));
	word[len] = '\0';
	*end = len;
	return word;
}

char* get_word1(int begin, int* end, char temp[], char* word)
{
	int len = 0;
	for (int i = begin;i < strlen(temp);i++)
	{
		while ((temp[i] >= 'A' && temp[i] <= 'Z') || (temp[i] >= 'a' && temp[i] <= 'z') || (temp[i] >= '0' && temp[i] <= '9'))
		{
			word = (char*)realloc(word, (len + 1) * sizeof(char));
			word[len] = temp[i];
			i++;
			len++;
		}
		break;
	}
	word = (char*)realloc(word, (len + 1) * sizeof(char));
	word[len] = '\0';
	*end = len;
	return word;
}

char* line_in_file(char* before, char* word, char* after, char* line)
{
	int len = 0;
	for (int i = 0;i < strlen(before);i++)
	{
		line = (char*)realloc(line, (len + 1) * sizeof(char));
		line[len] = before[i];
		len++;
	}
	for (int i = 0;i < strlen(word);i++)
	{
		line = (char*)realloc(line, (len + 1) * sizeof(char));
		line[len] = word[i];
		len++;
	}
	for (int i = 0;i < strlen(after);i++)
	{
		line = (char*)realloc(line, (len + 1) * sizeof(char));
		line[len] = after[i];
		len++;
	}
	line = (char*)realloc(line, (len + 1) * sizeof(char));
	line[len] = '\0';
	return line;
}
void rewrite(int counter, char* word1, char* word2, FILE* copy1, FILE* copy2)
{
	FILE* from;
	FILE* to;
	char* word;
	char smb;
	int* ind = 0;
	int new_len;
	word = (char*)calloc(1, sizeof(char));
	char* before;
	before = (char*)calloc(1, sizeof(char));
	char* after;
	after = (char*)calloc(1, sizeof(char));
	char temp[30];
	int begin = 0;
	if (counter % 2 == 1)
	{
		from = copy1;
		to = copy2;
		if ((from = fopen("copy1.txt", "r")) == NULL)
		{
			printf("открыть файл 1 не удалось\n");
			exit(1);
		}
		if ((to = fopen("copy2.txt", "w")) == NULL)
		{
			printf("открыть файл 2 не удалось\n");
			exit(1);
		}
	}
	else
	{
		from = copy2;
		to = copy1;
		if ((from = fopen("copy2.txt", "r")) == NULL)
		{
			printf("открыть файл 2 не удалось\n");
			exit(1);
		}
		if ((to = fopen("copy1.txt", "w")) == NULL)
		{
			printf("открыть файл 1 не удалось\n");
			exit(1);
		}
	}

	while ((fscanf(from, "%s", temp)) != EOF)
	{
		char* input_line;
		input_line = (char*)calloc(1, sizeof(char));
		before = get_symbols_before(begin, &begin, temp, before);
		word = get_word1(begin, &begin, temp, word);
		after = get_symbols_after(begin, &begin, temp, after);
		smb = fgetc(from);
		if (strcmp(word, word1) == 0)
		{
			input_line = line_in_file(before, word2, after, input_line);
			fputs(input_line, to);
			fputc(smb, to);
		}
		else if (strcmp(word, word2) == 0)
		{
			input_line = line_in_file(before, word1, after, input_line);
			fputs(input_line, to);
			fputc(smb, to);
		}
		else
		{
			fputs(temp, to);
			fputc(smb, to);
		}
		free(input_line);
	}
	free(before);
	free(word);
	free(after);
	fclose(from);
	fclose(to);
}

List* del_elements(List* head)
{
	List* temp = head;
	temp = head->next;
	List* temp1;
	temp1 = temp->next;
	free(head);
	free(temp);
	return temp1;
}

List* rearhive(List* head, FILE* copy1, FILE* copy2, int* number)
{
	List* temp;
	temp = head;
	List* word1;
	List* word2;
	int counter = 0;
	List* temp1 = temp->next;
	while (temp->next != NULL)
	{
		counter++;
		word1 = temp;
		word2 = temp->next;
		rewrite(counter, word1->word, word2->word, copy1, copy2);
		temp = del_elements(temp);
		if (temp == NULL)
			break;
	}
	*number = counter;
	return temp;
}
