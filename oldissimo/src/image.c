#include "image.h"

#include <stdlib.h>

/* Converting a <RGB IMAGE> to <YCC IMAGE> */
ycc_i rgbi2ycci(rgb_i img)
{
	ycc_i conv;
	int i, j;

	/* Creating a new matrix */
	conv.width	= img.width;
	conv.height	= img.height;
	conv.matrix	= (ycc_t**) malloc(sizeof(ycc_t*) * conv.height);
	for (i = 0; i < conv.height; i++)
		conv.matrix[i] = (ycc_t*) malloc(sizeof(ycc_t) * conv.width);

	/* Populating the matrix */
	for (i = 0; i < conv.height; i++)
		for (j = 0; j < conv.width; j++)
			conv.matrix[i][j] = rgb2ycc(img.matrix[i][j]);

	return conv;
};


/* Converting a <YCC IMAGE> to <RGB IMAGE> */
rgb_i ycci2rgbi(ycc_i img)
{
	rgb_i conv;
	int i, j;

	/* Creating a new matrix */
	conv.width	= img.width;
	conv.height	= img.height;
	conv.matrix	= (rgb_t**) malloc(sizeof(rgb_t*) * conv.height);
	for (i = 0; i < conv.height; i++)
		conv.matrix[i] = (rgb_t*) malloc(sizeof(rgb_t) * conv.width);

	/* Populating the matrix */
	for (i = 0; i < conv.height; i++)
		for (j = 0; j < conv.width; j++)
			conv.matrix[i][j] = ycc2rgb(img.matrix[i][j]);

	return conv;
};



void smooting(rgb_i *img, uint8_t mask)
{
	
};
void sharpening(rgb_i *img)
{
	int i,j;

	uint8_t xneg, xpos, yneg, ypos;

	for (i = 0; i < img->height; i++)
		for (j = 0; j < img->width; j++)
		{
			xneg = ((j - 1) < 0) ? (img->width - 1) : j - 1;
			xpos = j % img->width;
			yneg = ((i - 1) < 0) ? (img->height - 1) : i - 1;
			ypos = i % img->height;

			img->matrix[i][j].r = img->matrix[i][xneg].r + img->matrix[i][xpos].r + img->matrix[yneg][j].r + img->matrix[ypos][j].r - 4 * img->matrix[i][j].r;
			img->matrix[i][j].g = img->matrix[i][xneg].g + img->matrix[i][xpos].g + img->matrix[yneg][j].g + img->matrix[ypos][j].g - 4 * img->matrix[i][j].g;
			img->matrix[i][j].b = img->matrix[i][xneg].b + img->matrix[i][xpos].b + img->matrix[yneg][j].b + img->matrix[ypos][j].b - 4 * img->matrix[i][j].b;
		}
};