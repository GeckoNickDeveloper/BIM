#include "color.h"

/* Conversions */
ycc_t rgb2ycc(rgb_t c)
{
	ycc_t conv;

	conv.y	= 0		+ (0.299	* c.r) + (0.587		* c.g) + (0.114		* c.b);
	conv.cb	= 128	+ (0.168736	* c.r) + (0.331264	* c.g) + (0.5		* c.b);
	conv.cr	= 128	+ (0.5		* c.r) + (0.418688	* c.g) + (0.081312	* c.b);

	return conv;
};

rgb_t ycc2rgb(ycc_t c)
{
	rgb_t conv;

	conv.r = c.y								+ (1.402		* (c.cr - 128));
	conv.g = c.y - (0.344136	* (c.cb - 128))	- (0.714136		* (c.cr - 128));
	conv.b = c.y + (1.772		* (c.cb - 128));

	return conv;
};


/* Negative of a RGB color */
rgb_t negative(rgb_t c)
{
	rgb_t neg;

	neg.r = 255 - c.r;
	neg.g = 255 - c.g;
	neg.b = 255 - c.b;

	return neg;
};
