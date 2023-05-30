#include "Header.h"
char* get_line(char temp[], char* line)
{
	int i = 1, j = 0;
	while (temp[i] != '\n')
	{
		line[j] = temp[i];
		i++;
		j++;
	}
	line[j] = '\0';
	return line;
}

Tree* get_node(char temp_line[], Tree* node)
{
	char* line = (char*)calloc(strlen(temp_line), sizeof(char));
	line = get_line(temp_line, line);
	node->data = (char*)calloc(strlen(line), sizeof(char));
	strcpy(node->data, line);
	node->number = temp_line[0];
	node->left = NULL;
	node->right = NULL;
	return node;
}

int input_choice(int choice)
{
	int flag = 0;
	while (flag == 0) {
		printf("---1.YES\n---2.NO\n");
		scanf("%d", &choice);
		if (choice == 1)
			flag = 1;
		else if (choice == 2)
			flag = 1;
		else
		{
			flag = 0;
			printf("Wrong input. Try again\n");
		}
	}
	return choice;
}


Tree* input(FILE* f, Tree* node)
{
	char temp_line[SIZE];
	if (node->left != NULL && node->right != NULL) return node;
	while (fgets(temp_line, SIZE, f) != NULL) {
		if (temp_line[0] == '.') return node;
		else {
			Tree* temp = (Tree*)calloc(1, sizeof(Tree));
			temp = get_node(temp_line, temp);
			if (temp->number == '1') {
				temp = input(f, temp);
				node->left = temp;
			}
			else {
				temp = input(f, temp);
				node->right = temp;
				return node;
			}
		}
	}
	return node;
}

Tree* output(Tree* node)
{
	if (node == NULL)
		return node;
	else
	{
		printf("%s\n", node->data);
		node->left = output(node->left);
		node->right = output(node->right);
	}
	return node;
}

Tree* input_add(Tree* node, char* line, char num)
{
	node = (Tree*)calloc(1, sizeof(Tree));
	node->left = NULL;
	node->right = NULL;
	node->number = num;
	node->data = (char*)calloc(strlen(line), sizeof(char));
	strcpy(node->data, line);
	return node;
}

Tree* add_node(Tree* node, char* yes, char* no)
{
	char new_element[SIZE];
	char left = '1';
	char right = '0';
	node->number = '1';
	printf("Enter new question\n");
	getchar();
	gets(new_element);
	strcpy(node->data, new_element);
	node->left = input_add(node->left, no, left);
	node->right = input_add(node->right, yes, right);
	return node;
}

void help(Tree* node, int* flag)
{
	Tree* temp = node;
	int choice = 0;
	char greate[] = "GREATE!!!";
	char add[] = "I don't know this object. Do you want to add it in the database?";
	char* yes = (char*)calloc(strlen(greate), sizeof(char));
	strcpy(yes, greate);
	char* no = (char*)calloc(strlen(add), sizeof(char));
	strcpy(no, add);
	while ((*flag) == 0)
	{
		printf("-------%s\n", temp->data);
		if (strcmp(temp->data, yes) == 0)
		{
			(*flag) = 1;
		}
		else if (strcmp(temp->data, no) == 0)
		{
			temp = add_node(temp, yes, no);
			node = temp;
			(*flag) = 1;
			printf("The object is added\n");
		}
		else
		{
			choice = input_choice(choice);
			if (choice == 1)
				temp = temp->right;
			else
				temp = temp->left;
		}
		help(temp, flag);
	}
}


Tree* write_in_file(FILE** f, Tree* node)
{
	if (node != NULL)
	{
		fputc(node->number, *f);
		fwrite(node->data, strlen(node->data), 1, *f);
		fputc('\n', *f);
		if (node->left == NULL && node->right == NULL)
		{
			fputc('.', *f);
			fputc('\n', *f);
		}
		//fwrite(node->number,1, 1, *f);		
		node->left = write_in_file(f, node->left);
		node->right = write_in_file(f, node->right);

	}
	else return node;
	return node;
}
