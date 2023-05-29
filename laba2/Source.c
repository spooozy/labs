#include "Header.h"

int compare_and_push(List* head, char leks[], List* element)
{
	List* temp_compare = head;
	while (temp_compare != NULL)
	{
		if (strcmp(temp_compare->word, leks) == 0)
		{
			temp_compare->repeat++;
			return 1;
		}
		else temp_compare = temp_compare->next;
	}
	return 0;
}

char* get_word(char temp[], char* line)
{
	int len = 0;
	for (int i = 0;i <= strlen(temp); i++)
	{
		if ((temp[i] >= 'A' && temp[i] <= 'Z') || (temp[i] >= 'a' && temp[i] <= 'z') || (temp[i] >= '0' && temp[i] <= '9'))
		{

			line = (char*)realloc(line, (len + 1) * sizeof(char));
			line[len] = temp[i];
			len++;
		}
	}
	line = (char*)realloc(line, (len + 1) * sizeof(char));
	line[len] = '\0';
	return line;
}

List* add(List* head, char leks[])
{
	List* element;
	element = (List*)calloc(1, sizeof(List));
	element->next = NULL;
	element->repeat = 1;
	element->length = strlen(leks);
	element->word = (char*)calloc(strlen(leks), sizeof(char));
	strcpy(element->word, leks);
	if (head == NULL)
		head = element;
	else {
		if (compare_and_push(head, leks, element) == 1)
			return head;
		element->next = head;
		head = element;
	}
	return head;
}

void output(List* head)
{
	printf("\n");
	List* out = head;
	while (out != NULL)
	{
		printf("%-5d %-5d %s\n", out->length, out->repeat, out->word);
		out = out->next;
	}
}

List* find_word(List* head, List* element, List* word)
{
	List* temp = head;
	word = element;
	temp = head->next;
	int KPD = 0, kpd = 0, kpd_cmp = 0, dif = 0;
	while (temp != NULL)
	{
		kpd = element->length * element->repeat + temp->length * temp->repeat;
		kpd_cmp = element->length * temp->repeat + element->repeat * temp->length+element->length+temp->length+1;
		if (kpd_cmp < kpd)
		{
			dif = kpd - kpd_cmp;
			if (dif > KPD)
			{
				KPD = dif;
				word = temp;
			}
		}
		temp = temp->next;
	}
	return word;
}

void create_copy(FILE* f, FILE* copy)
{
	char temp_1[256];
	while (fgets(temp_1, 255, f) != NULL)
		fputs(temp_1, copy);
	fclose(copy);
}

void read_file(FILE* copy)
{
	char temp2[256];
	freopen("copy.txt", "r", copy);
	while (fgets(temp2, 255, copy) != NULL)
		printf("%s", temp2);
	fclose(copy);
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

void add_words(FILE* words, char* word1, char* word2, int counter)
{
	if (words == freopen("words.txt", "a", words) == NULL)
	{
		printf("открыть файл с словами не удалось\n");
		exit(1);
	}	
	fputs(word1, words);
	fputc(' ', words);
	fputs(word2, words);
	fputc(' ', words);
	//fputc('\n', words);
	fclose(words);
}

void rewrite(int counter, char* word1, char* word2, FILE* copy1, FILE* copy2, FILE* words)
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
	add_words(words, word1, word2, counter);
	fclose(from);
	fclose(to);
	//printf("111   ");
}

List* del_elements(List* head, List* word)
{
	List* temp = head;
	if (word == temp)
	{
		temp = head->next;
		free(head);
		return temp;
	}
	while (temp->next != NULL)
	{
		if (temp->next == word)
		{
			List* temp1;
			temp1 = temp->next;
			temp->next = temp1->next;
			free(temp1);
			return head;
		}
		temp = temp->next;
	}
}

List* arhiv(List* head, FILE* copy1, FILE* copy2, FILE* words, int* number_of_file)
{
	List* temp = head;
	List* word;
	word = head;
	int counter = 0;
	int flag = 0;
	while (temp != NULL)
	{
		word = find_word(head, temp, word);
		if (word != head)
		{
			counter++;
			rewrite(counter, temp->word, word->word, copy1, copy2, words);
			head = del_elements(head, word);
		}
		temp = temp->next;
		head = del_elements(head, head);
	}
	*number_of_file = counter;
	return head;
}

List* input(FILE* f, List* head)
{
	char* word;
	int counter = 0;
	char temp[30];
	while (!feof(f))
	{
		if (fscanf(f, "%s", temp) == EOF)	
			break;
		else
		{
			word = (char*)calloc(1, sizeof(char));
			word = get_word(temp, word);
			head = add(head, word);
			free(word);
		}
	}
	return head;
}



