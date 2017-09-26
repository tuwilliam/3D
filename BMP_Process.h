#include <stdio.h>  
#include <stdlib.h>  

typedef struct
{
	//unsigned short    bfType;  
	unsigned long    bfSize;
	unsigned short    bfReserved1;
	unsigned short    bfReserved2;
	unsigned long    bfOffBits;
} BitMapFileHeader;

typedef struct
{
	unsigned long  biSize;
	long   biWidth;
	long   biHeight;
	unsigned short   biPlanes;
	unsigned short   biBitCount;
	unsigned long  biCompression;
	unsigned long  biSizeImage;
	long   biXPelsPerMeter;
	long   biYPelsPerMeter;
	unsigned long   birUsed;
	unsigned long   birImportant;
} BitMapInfoHeader;

typedef struct
{
	unsigned char rgbBlue; //����ɫ����ɫ����  
	unsigned char rgbGreen; //����ɫ����ɫ����  
	unsigned char rgbRed; //����ɫ�ĺ�ɫ����  
	unsigned char rgbReserved; //����ֵ  
} RgbQuad;

typedef struct
{
	int width;
	int height;
	int channels;
	unsigned char* imageData;
}BMPImage;

BMPImage* LoadImage(char* path);
bool SaveImage(char* path, BMPImage* bmpImg);
void BinaryImage(BMPImage* img1, BMPImage* img2);