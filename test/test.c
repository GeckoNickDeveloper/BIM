#include <stdio.h>

#include "../src/color.h"
#include "../src/bitmap.h"

int main(void)
{
	image_t img;

	img = read_bitmap("bim_test.xbm");

	return 0;
}