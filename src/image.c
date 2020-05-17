#include "image.h"

#include <stdio.h>
#include <stdlib.h>

/* UTILS */
rgb_i* clone(rgb_i* img)
{
	rgb_i* clnd;
	int i, j;

	clnd = (rgb_i*) malloc(sizeof(rgb_i));

	clnd->width = img->width;
	clnd->height = img->height;

	clnd->matrix = (rgb_t**) malloc(sizeof(rgb_t*) * img->height);
	for (i = 0; i < img->height; i++)
		clnd->matrix[i] = (rgb_t*) malloc(sizeof(rgb_t) * img->width);
	
	for (i = 0; i < img->height; i++)
		for (j = 0; j < img->width; j++)
			clnd->matrix[i][j] = img->matrix[i][j];

	return clnd;
};

/* LIB FUNCS */
void smooting(rgb_i *img, uint8_t mSize)
{
	rgb_i* original = clone(img); /* Clono l'immagine originale */

	int x, y;	/* Contatori maschera */
	int i, j;	/* Contatori immagine */

	int rsum, gsum, bsum;
	int size_2;
	int k;

	/* La maschera deve essere dispari */
	if (mSize % 2 == 0)
		mSize++;
	size_2 = mSize / 2;
	
	/* Per ogni pixel */
	for (i = 0; i < img->height; i++)
		for (j = 0; j < img->width; j++)
		{

			rsum = gsum = bsum = 0;
			/* Calcolo i valori */
			for (y = 0 - size_2, k = 0; y < size_2; y++)
				for (x = 0 - size_2; x < size_2; x++)
				{
					if (!((i+y < 0) || (i+y >= img->height) || (j+x < 0) || (j+x >= img->width)))
					{
						rsum += original->matrix[i + y][j + x].r;
						gsum += original->matrix[i + y][j + x].g;
						bsum += original->matrix[i + y][j + x].b;
						k++;
					}
				}
			
			/* Inserimento del valore medio */
			img->matrix[i][j].r = rsum / k;
			img->matrix[i][j].g = gsum / k;
			img->matrix[i][j].b = bsum / k;
		}
};

void sharpening(rgb_i *img, double force)
{
	int i,j,x,y;
	rgb_i* original;
	double kernel[3][3] =	{
								{0, ((-1.0) * force), 0 },
								{((-1.0) * force), ((4.0) * force),	((-1.0) * force) },
								{0,	((-1.0) * force), 0}
							};

							/*
							 * [ 0] [-1] [ 0]
							 * [-1] [ 4] [-1]
							 * [ 0] [-1] [ 0]
							 *
							 *
							 * [-1] [-1] [-1]
							 * [-1] [ 8] [-1]
							 * [-1] [-1] [-1]
							 */

	double r,g,b;

	original = clone(img);

	for (i = 1; i < img->height - 1; i++)
		for (j = 1; j < img->width - 1; j++)
		{
			r = g = b = 0;
			for (y = -1; y < 2; y++)
				for (x = -1; x < 2; x++)
				{
					r += kernel[y + 1][x + 1] * ((double) original->matrix[i + y][j + x].r / 255); /* [/ 255] is for normalization */
					g += kernel[y + 1][x + 1] * ((double) original->matrix[i + y][j + x].g / 255); /* [/ 255] is for normalization */
					b += kernel[y + 1][x + 1] * ((double) original->matrix[i + y][j + x].b / 255); /* [/ 255] is for normalization */
				}
			
			img->matrix[i][j].r += ((r > 1.0) ? 1.0 : ((r < 0.0) ? 0.0 : r)) * 255;
			img->matrix[i][j].g += ((g > 1.0) ? 1.0 : ((g < 0.0) ? 0.0 : g)) * 255;
			img->matrix[i][j].b += ((b > 1.0) ? 1.0 : ((b < 0.0) ? 0.0 : b)) * 255;
		}
};

void complementar(rgb_i *img)
{
	int i,j;
	for (i = 0; i < img->height; i++)
		for (j = 0; j < img->width; j++)
			img->matrix[i][j] = negative(img->matrix[i][j]);
};