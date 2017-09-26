#include "BMP_Process.h"

BMPImage* LoadImage(char* path)
{
	BMPImage* bmpImg;
	FILE* pFile;
	unsigned short fileType;
	BitMapFileHeader bmpFileHeader;
	BitMapInfoHeader bmpInfoHeader;
	int channels = 1;
	int width = 0;
	int height = 0;
	int step = 0;
	int offset = 0;
	unsigned char pixVal;
	RgbQuad* quad;
	long i, j, k;

	bmpImg = (BMPImage*)malloc(sizeof(BMPImage));
	pFile = fopen(path, "rb");
	if (!pFile)
	{
		free(bmpImg);
		return NULL;
	}

	fread(&fileType, sizeof(unsigned short), 1, pFile);
	if (fileType == 0x4D42)
	{
		fread(&bmpFileHeader, sizeof(BitMapFileHeader), 1, pFile);

		fread(&bmpInfoHeader, sizeof(BitMapInfoHeader), 1, pFile);

		if (bmpInfoHeader.biBitCount == 8)
		{
			channels = 1;
			/*width = bmpInfoHeader.biWidth;
			height = bmpInfoHeader.biHeight;*/
			width = 640;
			height = 480;
			offset = (channels*width) % 4;
			if (offset != 0)
			{
				offset = 4 - offset;
			}

			bmpImg->width = width;
			bmpImg->height = height;
			bmpImg->channels = 1;
			bmpImg->imageData = (unsigned char*)malloc(sizeof(unsigned char)*width*height);
			step = channels*width;

			quad = (RgbQuad*)malloc(sizeof(RgbQuad) * 256);
			fread(quad, sizeof(RgbQuad), 256, pFile);
			free(quad);
			//fread(bmpImg->imageData, 1, width*height, pFile);
			fseek(pFile, 740 * 2592 + 300, SEEK_CUR);
			fread(bmpImg->imageData, 1, 640, pFile);
			for (i = 0; i < 479; i++) {
				fseek(pFile, 2592 - 640, SEEK_CUR);
				fread(bmpImg->imageData + 640 * (i+1), 1, 640, pFile);	//reverse image
			}
				
		}
	}

	return bmpImg;
}

bool SaveImage(char* path, BMPImage* bmpImg)
{
	FILE *pFile;
	unsigned short fileType;
	BitMapFileHeader bmpFileHeader;
	BitMapInfoHeader bmpInfoHeader;
	int step;
	int offset;
	unsigned char pixVal = '\0';
	int i, j;
	RgbQuad* quad;

	pFile = fopen(path, "wb");
	if (!pFile)
	{
		return false;
	}

	fileType = 0x4D42;
	fwrite(&fileType, sizeof(unsigned short), 1, pFile);
	
	if (bmpImg->channels == 1)//8位，单通道，灰度图  
	{
		step = bmpImg->width;
		offset = step % 4;
		if (offset != 4)
		{
			step += 4 - offset;
		}

		bmpFileHeader.bfSize = 54 + 256 * 4 + bmpImg->width;
		bmpFileHeader.bfReserved1 = 0;
		bmpFileHeader.bfReserved2 = 0;
		bmpFileHeader.bfOffBits = 54 + 256 * 4;
		fwrite(&bmpFileHeader, sizeof(BitMapFileHeader), 1, pFile);

		bmpInfoHeader.biSize = 40;
		bmpInfoHeader.biWidth = bmpImg->width;
		bmpInfoHeader.biHeight = bmpImg->height;
		bmpInfoHeader.biPlanes = 1;
		bmpInfoHeader.biBitCount = 8;
		bmpInfoHeader.biCompression = 0;
		bmpInfoHeader.biSizeImage = bmpImg->height*step;
		bmpInfoHeader.biXPelsPerMeter = 0;
		bmpInfoHeader.biYPelsPerMeter = 0;
		bmpInfoHeader.birUsed = 256;
		bmpInfoHeader.birImportant = 256;
		fwrite(&bmpInfoHeader, sizeof(BitMapInfoHeader), 1, pFile);

		quad = (RgbQuad*)malloc(sizeof(RgbQuad) * 256);
		for (i = 0; i<256; i++)
		{
			quad[i].rgbBlue = i;
			quad[i].rgbGreen = i;
			quad[i].rgbRed = i;
			quad[i].rgbReserved = 0;
		}
		fwrite(quad, sizeof(RgbQuad), 256, pFile);
		free(quad);

		fwrite(bmpImg->imageData, 1, bmpImg->width * bmpImg->height, pFile); //reverse image
	}

	fclose(pFile);

	return true;
}

void BinaryImage(BMPImage* binaryImg, BMPImage* img1, BMPImage* img2) {
	long i;
	*binaryImg = *img1;
	for (i = 0; i < img1->width * img1->height; i++)
		binaryImg->imageData[i] = (img1->imageData[i] > img2->imageData[i]) ? 255 : 0;
}