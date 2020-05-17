/**
 * @file		ppm.h
 * @author		Nicholas Kania
 * @brief		Header File for read and write PPM files
 * @version		0.1
 * @date		2020-05-15
 * 
 * @copyright	Copyright (c) 2020
 */

#ifndef PPM_H
#define PPM_H

#include "image.h"

/**
 * @fn		rgb_i* readPPM(const char* filename);
 * @param	filename	Path to the PPM file
 * @return	rgb_i*		Image structure
 * 
 * @brief	Read a PPM file
 */
extern rgb_i* readPPM(const char* filename);
/**
 * @fn		void writePPM(const char* filename, rgb_i *img);
 * @param	filename	Path to the PPM file
 * @param	img			Image to be written
 * 
 * @brief	Write a PPM file
 */
extern void writePPM(const char* filename, rgb_i *img);

#endif /* PPM_H */