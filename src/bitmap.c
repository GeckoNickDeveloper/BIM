#include "bitmap.h"

#include "color.h"

#include <stdint.h>
#include <stdio.h>

/*******************/

image_t read_bitmap(const char* filename)
{
	FILE* f;	/* Puntatore al file */

	BITMAPFILEHEADER		header;
	BITMAPINFOHEADER	info;
	image_t				img;

	/* Apertura del file selezionato */
	f = fopen(filename, "r");
	/* Inizio lettura */

	fread(&header, sizeof(BITMAPFILEHEADER), 1, f);
	printf("______ FILE HEADER ______\n\n");
	printf("TYPE\t\t>> \'%c%c\'\n", header.bfType, header.bfType >> 8);
	printf("SIZE\t\t>> %d\n", header.bfSize);
	printf("RESERVED 1\t\t>> %d\n", header.bfReserved1);
	printf("RESERVED 2\t\t>> %d\n", header.bfReserved2);
	printf("DATA-OFFSET\t\t>> %d\n", header.bfOffBits);

	fread(&info, sizeof(BITMAPINFOHEADER), 1, f);
	printf("\n______ INFOHEADER ______\n\n");
	printf("SIZE\t\t\t>> %d\n", info.biSize);
	printf("WIDTH\t\t\t>> %ld\n", info.biWidth);
	printf("HEIGHT\t\t\t>> %ld\n", info.biHeight);
	printf("PLANES\t\t\t>> %d\n", info.biPlanes);
	printf("BIT PER PIXEL\t\t>> %d\n", info.biBitCount);
	printf("COMPRESSION\t\t>> %d\n", info.biCompression);
	printf("IMAGE SIZE\t\t>> %d\n", info.biSizeImage);
	printf("X PIXELS PER M\t\t>> %ld\n", info.biXPelsPerMeter);
	printf("Y PIXELS PER M\t\t>> %ld\n", info.biYPelsPerMeter);
	printf("COLORS USED\t\t>> %d\n", info.biClrUsed);
	printf("IMPORTANT COLORS\t>> %d\n", info.biClrImportant);

	/* Fine lettura e chiusura file */
	fclose(f);

	return img;
};



void write_bitmap(const char* filename, const image_t* img)
{

};