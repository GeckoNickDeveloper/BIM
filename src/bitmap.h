#ifndef BITMAP_H
#define BITMAP_H

#include "color.h"
#include <stdint.h>

/*typedef struct _BITMAPHEADER
{
	char		signature[2];  'BM' 
	uint32_t	filesize;
	uint32_t	reserved;  = 0 
	uint32_t	reserved_;  = 0 
	uint32_t	dataOffset;
} BITMAPHEADER;

typedef struct _BITMAPINFOHEADER
{
	uint32_t size;
	uint32_t width;
	uint32_t height;
	uint16_t planes; = 1
	uint16_t bitsPerPixel; noi usiamo 24
	uint32_t compression;
	uint32_t imageSize;
	uint32_t XpixelsPerM;
	uint32_t YpixelsPerM;
	uint32_t colorsUsed;
	uint32_t importantColors;  = 0 	
} BITMAPINFOHEADER;*/

typedef struct _BITMAPFILEHEADER
{
	int16_t		bfType;
	int32_t		bfSize;
	int32_t		bfReserved1; 
	int32_t		bfReserved2; 
	int32_t		bfOffBits;
} BITMAPFILEHEADER;

typedef struct _BITMAPINFOHEADER
{
	int32_t	biSize;
	int64_t biWidth;
	int64_t biHeight;
	int16_t biPlanes;
	int16_t biBitCount;
	int32_t biCompression;
	int32_t biSizeImage;
	int64_t biXPelsPerMeter;
	int64_t biYPelsPerMeter;
	int32_t biClrUsed;	
	int32_t biClrImportant;
} BITMAPINFOHEADER;

extern image_t read_bitmap(const char* filename);
extern void write_bitmap(const char* filename, const image_t* img);

#endif /* BITMAP_H */