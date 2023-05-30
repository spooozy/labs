#include "Header.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	struct Cameras* TOP;
	FILE* f;
	int res = 0, j = 0, cam_num = 0;
	printf("The Best Film Cameras for Beginners\n");
	TOP = (struct Cameras*)calloc(1, sizeof(struct Cameras));
	char name_file[] = "<h3>";
	char format_file[] = "Film format:</strong>";
	char weight_file[] = "Weight:</strong>";
	char dimensions_file[] = "Dimensions:</strong>";
	char speed_file[] = "speed:</strong>";
	char buy_file[] = "Buy: $";
	f = fopen("TOP.txt", "r");
	TOP = input(TOP, f, name_file, format_file, weight_file, dimensions_file, speed_file, buy_file, &cam_num);
	fclose(f);
	menu(TOP, cam_num, res);
	return 0;
}
