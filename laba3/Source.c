#include "Header.h"
BIPMAP_header get_bmp(FILE* f)
{
	BIPMAP_header bmp;
	fread(&bmp.name, 2, 1, f);
	fread(&bmp.size, 3 * sizeof(int), 1, f);
	return bmp;
}

DIB_header get_dib(FILE* f)
{
	DIB_header dib;
	fread(&dib.header_size, 4, 1, f);
	fread(&dib.width, 4, 1, f);
	fread(&dib.height, 4, 1, f);
	fread(&dib.colorplanes, 2, 1, f);
	int size = dib.width * 3 + dib.width % 4;
	size = size * dib.height;
	dib.image_size = size;
	fread(&dib.bits_per_pixel, 2, 1, f);
	fread(&dib.compression, 4, 1, f);
	return dib;
}

void printf_headers(BIPMAP_header bmp, DIB_header dib)
{
	printf("Name:%c%c\nSize:%d\nOffset:%d\n", bmp.name[0], bmp.name[1], bmp.size, bmp.image_offset);
	printf("Header_size:%d\n", dib.header_size);
	printf("Width:%d\n", dib.width);
	printf("Height:%d\n", dib.height);
	printf("Colorplanes:%d\n", dib.colorplanes);
	printf("Bits_per_pixel:%d\n", dib.bits_per_pixel);
	printf("Compression:%d\n", dib.compression);
	printf("Image_size:%d\n", dib.image_size);
}

Image get_pixels(Image pic, DIB_header dib, BIPMAP_header bmp, FILE* f)
{
	pic.height = dib.height;
	pic.width = dib.width;
	fseek(f, bmp.image_offset, SEEK_SET);
	for (int i = pic.height - 1;i >= 0;i--) {
		pic.rgb[i] = (RGB*)malloc(pic.width * sizeof(RGB));
		for (int j = 0;j < pic.width;j++) {
			fread(&pic.rgb[i][j].blue, sizeof(char), 1, f);
			fread(&pic.rgb[i][j].green, sizeof(char), 1, f);
			fread(&pic.rgb[i][j].red, sizeof(char), 1, f);
		}
	}
	return pic;
}

FILE* choose_file()
{
	FILE* f;
	char line_1[] = "barashek";
	char line_2[] = "kot";
	char choice[10];
	printf("\nВыберите изображение для обработки\n1.(barashek) Барашек\n2.(kot)Кот\n");
	scanf("%s", &choice);
	//printf("%s\n", choice);
	if (strcmp(line_1, choice) == 0) {
		f = fopen("barashek.bmp", "rb");
		if (!f) {
			printf("7\n");
			fclose(f);
			exit(0);
		}
		printf("Изображение барашка готово к обработке\n");
	}
	else if (strcmp(line_2, choice) == 0)
	{
		f = fopen("kot.bmp", "rb");
		if (!f) {
			printf("7\n");
			fclose(f);
			exit(0);
		}
		printf("Изображение кота готово к обработке\n");
	}
	else {
		printf("Некорректный ввод. Программа завершается");
		return NULL;
	}
	return f;
}

int* get_red(int i, int j, int* m_red, Image pic)
{
	int num = 0;
	for (int n = i, n1 = 2;n1 >= 0;n--, n1--)
	{
		for (int m = j, m1 = 0; m1 < 3;m++, m1++)
		{
			m_red[num] = pic.rgb[n][m].red - '0';
			num++;
		}
	}
	return m_red;
}

int* get_green(int i, int j, int* m_green, Image pic)
{
	int num = 0;
	for (int n = i, n1 = 2;n1 >= 0;n--, n1--)
	{
		for (int m = j, m1 = 0; m1 < 3;m++, m1++)
		{
			m_green[num] = pic.rgb[n][m].green - '0';
			num++;
		}
	}
	return m_green;
}

int* get_blue(int i, int j, int* m_blue, Image pic)
{
	int num = 0;
	for (int n = i, n1 = 2;n1 >= 0;n--, n1--)
	{
		for (int m = j, m1 = 0; m1 < 3;m++, m1++)
		{
			m_blue[num] = pic.rgb[n][m].blue - '0';
			num++;
		}
	}
	return m_blue;
}

void sort(int* mas)
{
	for (int i = 0;i < sizeof(mas);i++)
	{
		for (int j = 0;j < sizeof(mas);j++)
			if (mas[j] > mas[j + 1])
			{
				int temp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = temp;
			}
	}
}

unsigned int grayscale(RGB rgb)
{
	return (0.3 * rgb.red) + (0.6 * rgb.green) + (0.1 * rgb.blue);
}

FILE* create_new_file(FILE* new, BIPMAP_header bmp, DIB_header dib, Image pic)
{
	fwrite(bmp.name, 2, 1, new);
	fwrite(&bmp.size, 3 * sizeof(int), 1, new);
	fwrite(&dib, sizeof(DIB_header), 1, new);
	int i;
	int j;
	for (i = pic.height - 1;i >= 0;i--) {
		for (j = 0;j < pic.width;j++) {
			fwrite(&pic.rgb[i][j].blue, sizeof(unsigned char), 1, new);
			fwrite(&pic.rgb[i][j].green, sizeof(unsigned char), 1, new);
			fwrite(&pic.rgb[i][j].red, sizeof(unsigned char), 1, new);
		}
	}
	fclose(new);
	return new;
}

void gray_colors(Image pic, DIB_header dib, BIPMAP_header bmp)
{
	Image temp_pic = pic;
	FILE* f_gray = fopen("gray_colors.bmp", "wb");
	if (!f_gray) {
		printf("7\n");
		fclose(f_gray);
		exit(0);
	}
	for (int i = 0;i < temp_pic.height;i++)
		for (int j = 0;j < temp_pic.width;j++)
			temp_pic.rgb[i][j].red = temp_pic.rgb[i][j].green = temp_pic.rgb[i][j].blue = grayscale(temp_pic.rgb[i][j]);
	f_gray = create_new_file(f_gray, bmp, dib, temp_pic);
	printf("Изображение переведено в оттенки серого\n");
}

unsigned int bl_wh(RGB rgb)
{
	int s = rgb.red + rgb.green + rgb.blue;
	if (s > (355 / 2 * 3))
	{
		rgb.red = rgb.green = rgb.blue = 255;
		return 255;
	}
	else
	{
		rgb.red = rgb.green = rgb.blue = 0;
		return 0;
	}
}

void bl_and_wh(Image pic, DIB_header dib, BIPMAP_header bmp)
{
	Image temp_pic = pic;
	FILE* f_bl_wh = fopen("black_and_white.bmp", "wb");
	if (!f_bl_wh) {
		printf("7\n");
		fclose(f_bl_wh);
		exit(0);
	}
	for (int i = 0;i < temp_pic.height;i++)
		for (int j = 0;j < temp_pic.width;j++)
			temp_pic.rgb[i][j].red = temp_pic.rgb[i][j].green = temp_pic.rgb[i][j].blue = bl_wh(temp_pic.rgb[i][j]);
	f_bl_wh = create_new_file(f_bl_wh, bmp, dib, temp_pic);
	printf("Изображение переведено в чёрно-белый\n");
}

void negativ(Image pic, DIB_header dib, BIPMAP_header bmp)
{
	Image temp_pic = pic;
	FILE* f_neg = fopen("negative.bmp", "wb");
	if (!f_neg) {
		printf("7\n");
		fclose(f_neg);
		exit(0);
	}
	for (int i = 0;i < temp_pic.height;i++)
		for (int j = 0;j < temp_pic.width;j++) {
			temp_pic.rgb[i][j].red = 255 - temp_pic.rgb[i][j].red;
			temp_pic.rgb[i][j].green = 255 - temp_pic.rgb[i][j].green;
			temp_pic.rgb[i][j].blue = 255 - temp_pic.rgb[i][j].blue;
		}
	f_neg = create_new_file(f_neg, bmp, dib, temp_pic);
	printf("Изображение переведено в негатив\n");
}

void gamma_correction(Image pic, DIB_header dib, BIPMAP_header bmp)
{
	Image temp_pic = pic;
	FILE* f_gamma = fopen("gamma_correction.bmp", "wb");
	if (!f_gamma) {
		printf("7\n");
		fclose(f_gamma);
		exit(0);
	}
	float g = 0.9;
	for (int i = dib.height - 1;i >= 0;i--)
	{
		for (int j = 0;j < dib.width;j++)
		{
			temp_pic.rgb[i][j].red = (255 * pow((temp_pic.rgb[i][j].red / 255.0f), g));
			temp_pic.rgb[i][j].green = (255 * pow((temp_pic.rgb[i][j].green / 255.0f), g));
			temp_pic.rgb[i][j].blue = (255 * pow((temp_pic.rgb[i][j].blue / 255.0f), g));
		}
	}
	f_gamma = create_new_file(f_gamma, bmp, dib, temp_pic);
	printf("Выполнена гамма-коррекция изображения \n");
}

void filt(Image pic, DIB_header dib, BIPMAP_header bmp)
{
	Image temp_pic = pic;
	FILE* f_filt = fopen("filtration.bmp", "wb");
	if (!f_filt) {
		printf("7\n");
		fclose(f_filt);
		exit(0);
	}
	int* m_red = (int*)calloc(9, sizeof(int));
	int* m_green = (int*)calloc(9, sizeof(int));
	int* m_blue = (int*)calloc(9, sizeof(int));
	for (int i = dib.height - 1;i >= 2;i--)
	{
		for (int j = 0;j < dib.width - 2;j++)
		{
			m_red = get_red(i, j, m_red, temp_pic);
			m_green = get_green(i, j, m_green, temp_pic);
			m_blue = get_blue(i, j, m_blue, temp_pic);
			sort(m_red);
			sort(m_green);
			sort(m_blue);
			temp_pic.rgb[i - 1][j + 1].red = m_red[4] + '0';
			temp_pic.rgb[i - 1][j + 1].green = m_green[4] + '0';
			temp_pic.rgb[i - 1][j + 1].blue = m_blue[4] + '0';
		}
	}
	f_filt = create_new_file(f_filt, bmp, dib, temp_pic);
	printf("Выполнена медианная фильтрация изображения \n");
}
