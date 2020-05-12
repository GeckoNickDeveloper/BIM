#include "ppm.h"

#include "image.h"

#include <stdio.h>
#include <stdlib.h>

rgb_i* readPPM(const char* filename)
{
	FILE*	f;
	char	sig[2];
	int w,h;
	int maxVal;
	int i,j;

	rgb_i *img = (rgb_i*) malloc(sizeof(rgb_i));
	

	f = fopen(filename, "r");
	fscanf(f, "%2c", sig);
	fscanf(f, "%d", &img->width);
	fscanf(f, "%d", &img->height);
	fscanf(f, "%d", &maxVal);
	
	img->matrix = (rgb_t**) malloc(sizeof(rgb_t*) * img->height);
	
	for (i = 0; i < img->height; i++)
		img->matrix[i] = (rgb_t*) malloc(sizeof(rgb_t) * img->width);
	
	for(i = 0; i < img->height; i++)
		for (j = 0; j < img->width; j++)
			fscanf(f, "%d %d %d", &img->matrix[i][j].r, &img->matrix[i][j].g, &img->matrix[i][j].b);

	fclose(f);

	return img;
};
void writePPM(const char* filename, rgb_i *img)
{
	FILE*	f;
	int maxVal;
	
	f = fopen(filename, "w");

	fprintf(f, "P3\n");
	fprintf(f, "%d ", img->width);
	fprintf(f, "%d\n", img->height);
	fprintf(f, "255\n");
	
	int i,j;
	for(i = 0; i < img->height; i++)
		for (j = 0; j < img->width; j++)
		{
			fprintf(f, "%d\n", img->matrix[i][j].r);
			fprintf(f, "%d\n", img->matrix[i][j].g);
			fprintf(f, "%d\n", img->matrix[i][j].b);
		}

	fclose(f);
};