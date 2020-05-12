#include "color.h"

/* Negative of a RGB color */
rgb_t negative(rgb_t c)
{
	rgb_t neg;

	neg.r = 255 - c.r;
	neg.g = 255 - c.g;
	neg.b = 255 - c.b;

	return neg;
};
