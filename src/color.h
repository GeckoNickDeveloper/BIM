#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

/* Color Model RGB */
typedef struct rgb
{
	uint8_t r;	/* Color Component >> RED	*/
	uint8_t g;	/* Color Component >> GREEN	*/
	uint8_t b;	/* Color Component >> BLUE	*/
} rgb_t;

typedef struct image
{
	rgb_t**		matrix;
	uint32_t	width;
	uint32_t	height;
} image_t;

/* Negative of a RGB color */
extern rgb_t negative(rgb_t c);

#endif /* COLOR_H */