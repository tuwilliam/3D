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
	unsigned char rgbBlue; //该颜色的蓝色分量  
	unsigned char rgbGreen; //该颜色的绿色分量  
	unsigned char rgbRed; //该颜色的红色分量  
	unsigned char rgbReserved; //保留值  
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
void BinaryImage(BMPImage* binaryImg, BMPImage* img1, BMPImage* img2);