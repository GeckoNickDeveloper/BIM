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

/* Color Model YCbCr */
typedef struct ycc
{
	uint8_t y;	/* Color Component >> LUMA						*/
	int8_t	cb;	/* Color Component >> BLUE-DIFFERENCE CHROMA	*/
	int8_t	cr;	/* Color Component >> RED-DIFFERENCE CHROMA		*/
} ycc_t;

/* Convertions */
extern ycc_t rgb2ycc(rgb_t c);
extern rgb_t ycc2rgb(ycc_t c);

/* Negative of a RGB color */
extern rgb_t negative(rgb_t c);

#endif /* COLOR_H */