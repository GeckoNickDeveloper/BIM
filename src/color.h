/**
 * @file		color.h
 * @author		Nicholas Kania
 * @brief		Header File for define color
 * @version		0.1
 * @date		2020-05-15
 * 
 * @copyright	Copyright (c) 2020
 */

#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

/**
 * @struct		rgb
 * @typedef		rgb_t
 * @brief		Color Model RGB
 */
typedef struct rgb
{
	uint8_t r;	/* Color Component >> RED	*/
	uint8_t g;	/* Color Component >> GREEN	*/
	uint8_t b;	/* Color Component >> BLUE	*/
} rgb_t;

/**
 * @fn		rgb_t negative(rgb_t c);
 * @param	c		The color to be elaborated
 * @return	rgb_t	The inverted color
 * 
 * @brief	Elaborate a color in order to return the negative color
 */
extern rgb_t negative(rgb_t c);

#endif /* COLOR_H */