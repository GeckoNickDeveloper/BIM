#include "jpeg.h"

#include <stdio.h>
#include <stdint.h>

#pragma pack(1)

/* EOI Marker is omitted */
typedef struct _JFIF
{
	/* SOI	Marker */
	uint8_t		SOI_mrk[2];		/* 0xFF 0xD8 */

	/* APP0	Marker */
	uint8_t		APP0_mrk[2];	/* 0xFF 0xE0 */
	uint16_t	APP0_length;	/* 0x00 0x10 */
	char		APP0_fId[5];	/* ['J', 'F', 'I', 'F', '\0'] */
	uint8_t		APP0_majorRev;	/* 1 */
	uint8_t		APP0_minorRev;	/* 1 */
	uint8_t		APP0_densUnit;	/* 0x00 >> not units	*/
								/* 0x01 >> dots/inch	*/
								/* 0x02 >> dots/cm		*/
	uint16_t	APP0_densX;		/* X Density			*/
	uint16_t	APP0_densY;		/* Y Density			*/
	uint8_t		APP0_wThumb;	/* must 0				*/
	uint8_t		APP0_hThumb;	/* must 0				*/

	/* DQT	Marker */
	uint8_t		DQT_mrk[2];		/* 0xFF 0xDB */
	uint16_t	DQT_length;		/* 67 */
	uint8_t		DQT_info;		/* bit [0...3] QT Number */ /* 0 */
								/* bit [4...7] Precision */ /* 0 = 8-bit*/
	int8_t		DQT_values[64];	/* 64 values (8 x 8) */

	/* SOF0	Marker */
	uint8_t		SOF0_mrk[2];	/* 0xFF 0xC0 */
	uint16_t	SOF0_length;	/* 8 + coponent * 3 */
	uint8_t		SOF0_precision;	/* 8 (bits/sample) */
	uint16_t	SOF0_img_width;
	uint16_t	SOF0_img_height;
	uint8_t		SOF0_nComps;	/* 3 */
	uint8_t		SOF0_comps[9];	/* 3 Byte a component:		*/
								/* Comp ID					*/
								/* Sampling factors			*/
								/* QT number				*/
								/* Repeat for 3 component	*/
	
	/* DHT	Marker */
	uint8_t		DHT_mrk[2];			/* 0xFF 0xC4*/
	uint16_t	DHT_length;			/* 0x001B */
	uint8_t		DHT_info;			/* 0x00 */
	uint8_t		DHT_nSymbols[16];	/* 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 */
	uint8_t		DHT_simbols[8];		/* 0 1 2 4 3 5 6 7 */
	
	/* SOS	Marker */
	uint8_t		SOS_mrk[2];
	uint16_t	SOS_length;			/* 6 + 2*(n comps) */
	uint8_t		SOS_nComps;			/* 3 */
	uint8_t		SOS_comps[6];		/* (CompID + HT) * comp */
	char		SOS_ignore[3];		/* To be ignored */
} JFIF;


void generateJFIF(JFIF* jfif, uint16_t w, uint16_t h)
{
	/* SOI Marker */
	jfif->SOI_mrk[0]		= 0xFF;
	jfif->SOI_mrk[1]		= 0xD8;

	/* APP0 Marker */
	jfif->APP0_mrk[0]		= 0xFF;
	jfif->APP0_mrk[1]		= 0xE0;
	jfif->APP0_length		= 0x0010;
	jfif->APP0_fId[0]		= 'J';
	jfif->APP0_fId[1]		= 'F';
	jfif->APP0_fId[2]		= 'I';
	jfif->APP0_fId[3]		= 'F';
	jfif->APP0_fId[4]		= '\0';
	jfif->APP0_majorRev		= 0x01;
	jfif->APP0_minorRev		= 0x01;
	jfif->APP0_densUnit		= 0x01;
	jfif->APP0_densX		= 0x012C;
	jfif->APP0_densY		= 0x012C;
	jfif->APP0_wThumb		= 0x00;
	jfif->APP0_wThumb		= 0x00;

	/* DQT Marker */
	jfif->DQT_mrk[0]		= 0xFF;
	jfif->DQT_mrk[1]		= 0xDB;
	jfif->DQT_length		= 0x0043;
	jfif->DQT_info			= 0x00;
	/* Quantization Table Values (64) */
	jfif->DQT_values[0]		= 16;
	jfif->DQT_values[1]		= 11;
	jfif->DQT_values[2]		= 10;
	jfif->DQT_values[3]		= 16;
	jfif->DQT_values[4]		= 24;
	jfif->DQT_values[5]		= 40;
	jfif->DQT_values[6]		= 51;
	jfif->DQT_values[7]		= 61;
	jfif->DQT_values[8]		= 12;
	jfif->DQT_values[9]		= 12;
	jfif->DQT_values[10]	= 14;
	jfif->DQT_values[11]	= 19;
	jfif->DQT_values[12]	= 26;
	jfif->DQT_values[13]	= 58;
	jfif->DQT_values[14]	= 60;
	jfif->DQT_values[15]	= 55;
	jfif->DQT_values[16]	= 14;
	jfif->DQT_values[17]	= 13;
	jfif->DQT_values[18]	= 16;
	jfif->DQT_values[19]	= 24;
	jfif->DQT_values[20]	= 40;
	jfif->DQT_values[21]	= 57;
	jfif->DQT_values[22]	= 69;
	jfif->DQT_values[23]	= 56;
	jfif->DQT_values[24]	= 14;
	jfif->DQT_values[25]	= 17;
	jfif->DQT_values[26]	= 22;
	jfif->DQT_values[27]	= 29;
	jfif->DQT_values[28]	= 51;
	jfif->DQT_values[29]	= 87;
	jfif->DQT_values[30]	= 80;
	jfif->DQT_values[31]	= 62;
	jfif->DQT_values[32]	= 18;
	jfif->DQT_values[33]	= 22;
	jfif->DQT_values[34]	= 37;
	jfif->DQT_values[35]	= 56;
	jfif->DQT_values[36]	= 68;
	jfif->DQT_values[37]	= 109;
	jfif->DQT_values[38]	= 103;
	jfif->DQT_values[39]	= 77;
	jfif->DQT_values[40]	= 24;
	jfif->DQT_values[41]	= 35;
	jfif->DQT_values[42]	= 55;
	jfif->DQT_values[43]	= 64;
	jfif->DQT_values[44]	= 81;
	jfif->DQT_values[45]	= 104;
	jfif->DQT_values[46]	= 113;
	jfif->DQT_values[47]	= 92;
	jfif->DQT_values[48]	= 49;
	jfif->DQT_values[49]	= 64;
	jfif->DQT_values[50]	= 78;
	jfif->DQT_values[51]	= 87;
	jfif->DQT_values[52]	= 103;
	jfif->DQT_values[53]	= 121;
	jfif->DQT_values[54]	= 120;
	jfif->DQT_values[55]	= 101;
	jfif->DQT_values[56]	= 72;
	jfif->DQT_values[57]	= 92;
	jfif->DQT_values[58]	= 95;
	jfif->DQT_values[59]	= 98;
	jfif->DQT_values[60]	= 112;
	jfif->DQT_values[61]	= 100;
	jfif->DQT_values[62]	= 103;
	jfif->DQT_values[63]	= 99;
	
	/* SOF0 Marker */
	jfif->SOF0_mrk[0]		= 0xFF;
	jfif->SOF0_mrk[1]		= 0xC0;
	jfif->SOF0_length		= 0x0011;/* 8 + (components [3] * 3) */;
	jfif->SOF0_precision	= 0x08;
	jfif->SOF0_img_width	= w;
	jfif->SOF0_img_height	= h;
	jfif->SOF0_nComps		= 0x03;
	jfif->SOF0_comps[0]		= 0x01;
	jfif->SOF0_comps[1]		= 0x11;
	jfif->SOF0_comps[2]		= 0x00;
	jfif->SOF0_comps[3]		= 0x02;
	jfif->SOF0_comps[4]		= 0x11;
	jfif->SOF0_comps[5]		= 0x00;
	jfif->SOF0_comps[6]		= 0x03;
	jfif->SOF0_comps[7]		= 0x11;
	jfif->SOF0_comps[8]		= 0x00;
	
	/* DHT Marker */
	jfif->DHT_mrk[0]		= 0xFF;
	jfif->DHT_mrk[1]		= 0xC4;
	jfif->DHT_length		= 0x001B;
	jfif->DHT_info			= 0x00;
	jfif->DHT_nSymbols[0]	= 0x01;
	jfif->DHT_nSymbols[1]	= 0x01;
	jfif->DHT_nSymbols[2]	= 0x01;
	jfif->DHT_nSymbols[3]	= 0x01;
	jfif->DHT_nSymbols[4]	= 0x01;
	jfif->DHT_nSymbols[5]	= 0x01;
	jfif->DHT_nSymbols[6]	= 0x01;
	jfif->DHT_nSymbols[7]	= 0x01;
	jfif->DHT_nSymbols[8]	= 0x00;
	jfif->DHT_nSymbols[9]	= 0x00;
	jfif->DHT_nSymbols[10]	= 0x00;
	jfif->DHT_nSymbols[11]	= 0x00;
	jfif->DHT_nSymbols[12]	= 0x00;
	jfif->DHT_nSymbols[13]	= 0x00;
	jfif->DHT_nSymbols[14]	= 0x00;
	jfif->DHT_nSymbols[15]	= 0x00;
	jfif->DHT_simbols[0]	= 0x00;
	jfif->DHT_simbols[1]	= 0x01;
	jfif->DHT_simbols[2]	= 0x02;
	jfif->DHT_simbols[3]	= 0x04;
	jfif->DHT_simbols[4]	= 0x03;
	jfif->DHT_simbols[5]	= 0x05;
	jfif->DHT_simbols[6]	= 0x06;
	jfif->DHT_simbols[7]	= 0x07;

	/* SOS Marker */
	jfif->SOS_mrk[0]		= 0xFF;
	jfif->SOS_mrk[1]		= 0xDA;
	jfif->SOS_length		= 0x000C;
	jfif->SOS_nComps		= 0x03;
	jfif->SOS_comps[0]		= 0x01;
	jfif->SOS_comps[1]		= 0x00;
	jfif->SOS_comps[2]		= 0x02;
	jfif->SOS_comps[3]		= 0x00;
	jfif->SOS_comps[4]		= 0x03;
	jfif->SOS_comps[5]		= 0x00;
	jfif->SOS_ignore[0]		= 0x00;
	jfif->SOS_ignore[1]		= 0x00;
	jfif->SOS_ignore[2]		= 0x00;
};


rgb_i readJPEG(const char* filename)
{

};

void writeJPEG(const char* filename, rgb_i img)
{
	JFIF			header;
	FILE			*f;
	const uint16_t	EOI 	= 0xFFD9;

	generateJFIF(&header, img.width, img.width);

	/* File writing */
	f = fopen(filename, "w");

	/* Headers Marker */
	fwrite(&header, sizeof(JFIF), 1, f);
	
	int i;
	uint8_t v;
	for (i = 0, v = 12; i < img.width * img.height * 3; i++)
		fwrite(&v, sizeof(uint8_t), 1, f);
	/* EOI Marker */
	fwrite(&EOI, sizeof(uint16_t), 1, f);

	fclose(f);
};