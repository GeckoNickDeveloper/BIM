#ifndef PPM_H
#define PPM_H

#include "image.h"

extern rgb_i* readPPM(const char* filename);
extern void writePPM(const char* filename, rgb_i *img);

#endif /* PPM_H */