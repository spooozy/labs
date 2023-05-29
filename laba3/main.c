#include "Header.h"

int main()
{
	setlocale(LC_ALL, "rus");
	FILE* f;
	int choice;
	do {
		f = choose_file();
		if (f == NULL)
			return 0;
		BIPMAP_header bmp;
		DIB_header dib;
		bmp = get_bmp(f);
		dib = get_dib(f);
		Image pic;
		pic.rgb = (RGB**)malloc(dib.height * sizeof(void*));
		pic = get_pixels(pic, dib, bmp, f);
		fclose(f);
		printf("\nВыберите вариант обработки\n1. Оттенки серого\n2. Чёрно-белый\n3. Негатив\n4. Гамма-Коррекция\n5. Медианная фильтрация\n6. Выход\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			gray_colors(pic,dib,bmp);
			break;
		case 2:
			bl_and_wh(pic, dib, bmp);
			break;
		case 3:
			negativ(pic, dib, bmp);
			break;
		case 4:
			gamma_correction(pic, dib, bmp);
			break;
		case 5:
			filt(pic, dib, bmp);
			break;
		case 6:
			printf("Выход из программы\n");
			return 0;
			break;
		}
	} while (1);
	return 0;
}
