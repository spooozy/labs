#include "Header.h"

int main()
{
	FILE* f = fopen("HansZimmer.txt", "r");
	FILE** new = fopen("new.txt", "w");
	char file[] = "HansZimmer.txt";
	char temp_file[] = "new.txt";
	char del[] = "del.txt";
	int* flag = 0;
	char temp_line[255];
	fgets(temp_line, 100, f);
	Tree* root;
	root = (Tree*)calloc(1, sizeof(Tree));
	root->left = NULL;
	root->right = NULL;
	root->number = temp_line[0];
	char* line = (char*)calloc(1, sizeof(char));
	line = get_line(temp_line, line);
	root->data = (char*)calloc(sizeof(line), sizeof(char));
	strcpy(root->data, line);		
	root = input(f, root);
	fclose(f);
	help(root, &flag);
	root = write_in_file(&new, root);
	fclose(new);
	rename(file, del);
	rename(temp_file, file);	
	remove(del);
	return 0;
}
