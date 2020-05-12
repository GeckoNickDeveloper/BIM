#include "../src/color.h"
#include "../src/ppm.h"
#include "../src/image.h"

#include <stdio.h>

#define ORIGINAL	"./img/ldr.ppm"
#define NEGATIVE	"./img/negative.ppm"
#define SMOOTH		"./img/output/smooth.ppm"
#define SHARP		"./img/output/sharp.ppm"
#define OUTPUT		"./img/output/dafaq.ppm"

int main(void)
{
	rgb_i* img = readPPM(ORIGINAL);
	

	int i,j;
	for (i = 0; i < img->height; i++)
		for (j = 0; j < img->width; j++) {
			img->matrix[i][j] = negative(img->matrix[i][j]);
		}
	/*sharpening(img, 0.5);*/

	writePPM(NEGATIVE, img);

	return 0;
}