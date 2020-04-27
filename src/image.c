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