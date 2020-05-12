#include <stdio.h>

/*#include "../src/color.h"
#include "../src/jpeg.h"*/

int main(void)
{
	FILE* f;
	f = fopen("./img/wgimp.jpg", "r");

	int i;

	for (i = 0; i < 256; i++)
	{
		char c;
		fread(&c, 1, 1, f);
		printf("%d\t>> %x\n\n", i, c & 0xFF);
	}

	fclose(f);

	return 0;
}