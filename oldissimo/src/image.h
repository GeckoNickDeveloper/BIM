#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"

/*
 * IMPORTANT:
 * 
 * images are defined <color model>_i, where i stands for <image>
 */

/* Uncompressed RGB Image Structure */
typedef struct rgbimage
{
	rgb_t**		matrix;
	uint16_t	width;
	uint16_t	height;
} rgb_i;

/* Uncompressed YCC Image Structure */
typedef struct yccimage
{
	ycc_t**		matrix;
	uint16_t	width;
	uint16_t	height;
} ycc_i;

extern ycc_i rgbi2ycci(rgb_i img);
extern rgb_i ycci2rgbi(ycc_i img);

/* smoothing = (1/K) sum from {i = 0} to { mask^2} {z_i} */
/* sharpening = f(x+1, y) + f(x-1, y) + f(x, y+1) + f(x, y-1) - 4f(x, y) */

extern void smooting(rgb_i *img, uint8_t mask);
extern void sharpening(rgb_i *img);

#endif /* IMAGE_H */