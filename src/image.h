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
	uint32_t	width;
	uint32_t	height;
} rgb_i;

/* Uncompressed YCC Image Structure */
typedef struct yccimage
{
	ycc_t**		matrix;
	uint32_t	width;
	uint32_t	height;
} ycc_i;

extern ycc_i rgbi2ycci(rgb_i img);
extern rgb_i ycci2rgbi(ycc_i img);

#endif /* IMAGE_H */