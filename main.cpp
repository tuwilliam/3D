#include "BMP_Process.h"

int main()
{
	int i;
	char strBuf[100];
	BMPImage* img[22];

	for (i = 0; i < 22; i++) {
		sprintf(strBuf, "img_output_cup_gray/image%d.bmp", i+1);
		img[i] = LoadImage(strBuf);
	}

	for (i = 0; i < 20; i+=2) {
		BinaryImage(img[i], img[i+1]);
	}

	for (i = 0; i < 20; i += 2) {
		sprintf(strBuf, "result%d.bmp", i + 1);
		if (SaveImage(strBuf, img[i])) {
			printf("save ok... \n");
		}
	}
	
	return 0;
}