#include "BMP_Process.h"

int main()
{
	int i;
	char strBuf[100];
	BMPImage* img[22];
	BMPImage* binaryImg[10];

	//for (i = 0; i < 22; i++) {
	//	sprintf(strBuf, "img_output_cup_gray/image%d.bmp", i+1);
	//	img[i] = LoadImage(strBuf);
	//}
	img[0] = LoadImage("img_output_cup_gray/image7.bmp");
	//for (i = 0; i < 20; i+=2) {
	//	sprintf(strBuf, "img_output_cup_gray/image%d.bmp", i + 1);
	//	img[i] = LoadImage(strBuf);
	//}

	//BinaryImage(binaryImg[0], img[10], img[11]);

	if (SaveImage("result.bmp", img[0])) {
		printf("save ok... \n");
	}

	return 0;
}