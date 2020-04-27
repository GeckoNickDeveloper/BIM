#ifndef JPEG_H
#define JPEG_H

#include "image.h"
#include "color.h"

extern rgb_i readJPEG(const char* filename);
extern void writeJPEG(const char* filename, rgb_i img);

#endif /* JPEG_H */