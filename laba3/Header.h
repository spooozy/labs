#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "locale.h"
#include <string.h>
#pragma pack(1)
typedef struct {
	char name[2];
	unsigned int size;
	unsigned short unused1;
	unsigned short unused2;
	unsigned int image_offset;
} BIPMAP_header;

typedef struct {
	unsigned int header_size;
	unsigned int width;
	unsigned int height;
	unsigned short int colorplanes;
	unsigned short int bits_per_pixel;
	unsigned int compression;
	unsigned int image_size;
	unsigned int temp[4];
}DIB_header;

typedef struct {
	unsigned char blue;
	unsigned char green;
	unsigned char red;
} RGB;

typedef struct {
	int height;
	int width;
	RGB** rgb;
}Image;
#pragma pop
BIPMAP_header get_bmp(FILE* f);
DIB_header get_dib(FILE* f);
void printf_headers(BIPMAP_header bmp, DIB_header dib);
Image get_pixels(Image pic, DIB_header dib, BIPMAP_header bmp, FILE* f);
FILE* choose_file();
int* get_red(int i, int j, int* m_red, Image pic);
int* get_green(int i, int j, int* m_green, Image pic);
int* get_blue(int i, int j, int* m_blue, Image pic);
void sort(int* mas);
unsigned int grayscale(RGB rgb);
FILE* create_new_file(FILE* new, BIPMAP_header bmp, DIB_header dib, Image pic);
void gray_colors(Image pic, DIB_header dib, BIPMAP_header bmp);
unsigned int bl_wh(RGB rgb);
void bl_and_wh(Image pic, DIB_header dib, BIPMAP_header bmp);
void negativ(Image pic, DIB_header dib, BIPMAP_header bmp);
void gamma_correction(Image pic, DIB_header dib, BIPMAP_header bmp);
void filt(Image pic, DIB_header dib, BIPMAP_header bmp);


