#include "../src/color.h"
#include "../src/ppm.h"
#include "../src/image.h"

#include <stdio.h>

#define LDR				"./img/ldr.ppm"
#define LADYMARIA		"./img/ladymaria.ppm"
#define FORHONOR		"./img/forhonor.ppm"
#define HOLLOWKNIGHT	"./img/hollowknight.ppm"
#define SMOOTH			"./img/output/smooth.ppm"
#define SHARP			"./img/output/sharp.ppm"
#define OUTPUT			"./img/output/default.ppm"

int main(void)
{
	rgb_i* img = readPPM(LADYMARIA);
	
	sharpening(img, 0.5);

	writePPM(SHARP, img);

	return 0;
}