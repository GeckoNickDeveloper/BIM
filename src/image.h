/**
 * @file		image.h
 * @author		Nicholas Kania
 * @brief		Header File for image manipulation
 * @version		0.1
 * @date		2020-05-15
 * 
 * @copyright	Copyright (c) 2020
 */

#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"

/*
 * IMPORTANT:
 * 
 * images are defined <color model>_i, where i stands for <image>
 */

/**
 * @struct		rgbimage
 * @typedef		rgb_i
 * @brief		Data structure for rappresent uncompressed image data
 */
typedef struct rgbimage
{
	rgb_t**		matrix;	/** @property	matrix	 Image Pixel Matrix	*/
	uint16_t	width;	/** @property	width	 Image Width			*/
	uint16_t	height;	/** @property	height	 Image Height			*/
} rgb_i;

/**
 * @fn			void smooting(rgb_i *img, uint8_t mSize);
 * @param		img		Image to be smoothed
 * @param		mSize	Size of the smoothing mask
 * 
 * @brief		Smooth an image with a given mask size
 */
extern void smooting(rgb_i *img, uint8_t mSize);
/**
 * @fn			void sharpening(rgb_i *img, double force);
 * @param		img		Image to be smoothed
 * @param		force	Force of the sharpening
 * 
 * @brief		Sharpen an image with a given force
 */
extern void sharpening(rgb_i *img, double force);
/**
 * @fn			void complementar(rgb_i *img);
 * @param		img		Image to be modifyed
 * 
 * @brief		Create the negative of the image
 */
extern void complementar(rgb_i *img);


#endif /* IMAGE_H */