#ifndef JPEG_H
#define JPEG_H

#include "image.h"
#include "color.h"

/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************************************************************/

typedef struct _MARKER
{
	int8_t	mIdentifier[2];	/* Marker Identifier: 0xFF 0xXX					*/
							/* where 0xXX identifies the specific marker	*/
} MARKER;

typedef struct _APP0MARKER
{
	short	mLength;	/* Length of the markers in bytes				*/
	char	fmIdent[5];	/* File Marker Identifier: 4 characters + '\0'	*/
	int8_t	majorRev;	/* Mmajor Revision Number [xx.00]				*/
	int8_t	minorRev;	/* Minor Revision Number [00.xx]				*/
	int8_t	dUnits;		/* 0x00 >> not units (x/y aspect ratio)			*/
						/* 0x01 >> dots/inch							*/
						/* 0x02 >> dots/cm								*/
	short	densX;		/* X Density									*/
	short	densY;		/* Y Density									*/
	int8_t	wThumb;		/* Thumbnail Width								*/
	int8_t	hThumb;		/* Thumbnail Height								*/
	rgb_t*	thumb;		/* Thumbnail ([wThumb * hThumb] RGB elements)	*/
} APP0MARKER;

typedef struct _DHTMARKER
{
	short	mLength;	/* Length of the Huffman Table		*/
	int8_t	htInfo;		/* Huffman Table Info				*/
						/* bit [0...3]	>> number of HT		*/
						/* bit [4]		>> type of HT		*/
						/*		[0] >> DC Table				*/
						/*		[1] >> DC Table				*/
						/* bit [5...7] not used (must be 0) */
	int8_t	nSymbols;	/* Number of Symbols				*/
	int8_t*	symbols;	/* N Simbols, where [N = n ofcodes]	*/
} DHTMARKER;

typedef struct _DRIMARKER
{
	short	mLength;		/* Length of the marker (must be 4)							*/
	short	rstInterval;	/* This is in units of MCU blocks, means that every n MCU	*/
							/* blocks a RSTn marker can be found. The first marker will	*/
							/*be RST0, then RST1 etc, after RST7 repeating from RST0.	*/
} DRIMARKER;

typedef struct _DQTMARKER
{
	short	mLength;	/* Length of the Quantization Table							*/
	int8_t	qtInfo;		/* Quantization Table Info									*/
						/* bit [0...3] >> number of QT [(0...3) otherwise error]	*/
						/* bit [4...7] >> precision									*/
						/* 		0			= 8 bit									*/
						/* 		Otherwise	= 16 bit								*/
	int8_t*	symbols;	/* N Bytes. This gives QT values.							*/
						/* [n = 64 * (precision + 1)]								*/
} DQTMARKER;

/* The Image Data (scans) is immediatly following the SOS segment */
typedef struct _SOSMARKER
{
	short	mLength;	/* Must be equal to [6 + 2 * (n-components in scan)]				*/
	int8_t	nComp;		/* Number of Components in Scan. Must be [1, 4], error otherwise	*/
						/* Usually 1 or 3													*/
	int8_t*	comps;		/* For each component, 2 Bytes										*/
						/* 1 Byte >> Component ID											*/
						/* 		[0x01] >> Y													*/
						/* 		[0x01] >> Cb												*/
						/* 		[0x01] >> Cr												*/
						/* 		[0x01] >> I													*/
						/* 		[0x05] >> Q													*/
						/* 1 Byte >> Huffman Table to use:									*/
						/* 		bit [0...3] >> AC Table (0...3)								*/
						/* 		bit [4...7] >> DC Table (0...3)								*/
	int8_t	ignore[3];	/* Bytes to SKIP													*/
} SOSMARKER;

/* ========== JFIF FILE STRUCTURE ========== */
/* JFIF MARKER (GENERIC) */
typedef struct _JFIFMARKER
{
	MARKER	mID;	/* Marker 2 Bytes [0xFF 0xXX]				*/
	void*	marker;	/* Pointer to the real marker [var. size]	*/
} JFIFMARKER;

/* List of Markers */
typedef struct _JFIF
{
	JFIFMARKER marker;
	struct _JFIF* next;
} JFIF;

/* ========== JFIF FILE STRUCTURE ========== */

typedef struct _JFIFIMG
{
	JFIF*	mrkH;
	JFIF*	mrkT;

	rgb_i	pxldata;	
} JFIFIMG;


extern JFIFIMG readJPEG(const char* filename);
extern void writeJPEG(const char* filename, rgb_i img);

#endif /* JPEG_H */