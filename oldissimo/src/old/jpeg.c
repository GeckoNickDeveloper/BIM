#include "jpeg.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#pragma pack(1)

/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************************************************************/

#define MRK		0xFF

#define SOI 	0xD8
#define APP0 	0xE0
#define DHT 	0xC4
#define DQT 	0xDB
#define DRI 	0xDD
#define SOS 	0xDA
#define EOI 	0xD9

/* MARKER ONLY (NO SIZE). IGNORE */
#define RST0	0xD0   /* RSTn are used for resync, may be ignored */
#define RST1	0xD1
#define RST2	0xD2
#define RST3	0xD3
#define RST4	0xD4
#define RST5	0xD5
#define RST6	0xD6
#define RST7	0xD7
#define TEM		0x01

/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************************************************************/

/* Utils */
void insertMarker(JFIF** head, JFIF** tail, JFIFMARKER mrk)
{
	JFIF* newItem;

    newItem = (JFIF*) malloc(sizeof(JFIF));
    newItem->marker = mrk;
    newItem->next = NULL;

    if (*head != NULL)
        (*head)->next = newItem;

    else
        *tail = newItem;

    *head = newItem;
};

JFIF* removeMarker(JFIF** head, JFIF** tail, JFIFMARKER mrk)
{
	JFIF* item;

    item = *tail;

    if (*tail != NULL)
    {
        *tail = (*tail)->next;
       
        if (*tail == NULL)
            *head = NULL;
    }

    return(item);
};

/* FILE READING */
void readMarkers(JFIF** head, JFIF** tail, FILE* stream)
{
	JFIFMARKER*	node;			/* Marker to be read	*/
	int			errNode = 0;	/* Errore in Node flag	*/
	int			cScan = 1;		/* Continue Scan flag	*/

	/* POINTERS FOR READIBILITY */
	APP0MARKER*	mAPP0;
	DHTMARKER*	mDHT;
	DQTMARKER*	mDQT;
	DRIMARKER*	mDRI;
	SOSMARKER*	mSOS;
	

	do
	{
		node			= (JFIFMARKER*) malloc(sizeof(JFIFMARKER));
		node->marker	= NULL;
		fread(&node->mID, sizeof(MARKER), 1, stream);
		if (node->mID.mIdentifier[0] != MRK)
		{
			errNode	= 1;
			cScan	= 0;
		}
		else
		{
			switch (node->mID.mIdentifier[1])
			{
			case APP0:
				mAPP0 = (APP0MARKER*) malloc(sizeof(APP0MARKER));

				fread(&mAPP0->mLength, sizeof(short), 1, stream);
				fread(&mAPP0->fmIdent, sizeof(char), 5, stream);
				
				/* File not in JFIF Format */
				if ((strcmp(mAPP0->fmIdent, "JFIF") == 0) && (mAPP0->mLength >= 16))
				{
					fread(&mAPP0->majorRev, sizeof(int8_t), 1, stream);
					fread(&mAPP0->minorRev, sizeof(int8_t), 1, stream);
					fread(&mAPP0->densX, sizeof(short), 1, stream);
					fread(&mAPP0->densY, sizeof(short), 1, stream);
					fread(&mAPP0->wThumb, sizeof(int8_t), 1, stream);
					fread(&mAPP0->hThumb, sizeof(int8_t), 1, stream);
					mAPP0->thumb = (rgb_t*) malloc(sizeof(rgb_t) * mAPP0->wThumb * mAPP0->hThumb);

					/*fread(&mAPP0->mLength, sizeof(), 1, stream);*/

					/* Inserting in JFIF */
					node->marker = mSOS;
					insertMarker(head, tail, *node);
				}
				else
				{
					errNode	= 1;
					cScan	= 0;
				}
				break;
			case DHT:
				
				insertMarker(head, tail, *node);
				break;
			case DQT:

				insertMarker(head, tail, *node);
				break;
			case DRI:

				insertMarker(head, tail, *node);
				break;
			case SOS:
				mSOS = (SOSMARKER*) malloc(sizeof(SOSMARKER));
				/*fread(&node->marker[0 /* mLength *], sizeof(short), 1, stream);
				/*fread(&node->marker[2 /* nComp *], sizeof(int8_t), 1, stream);*/
				fread(&mSOS->mLength, sizeof(short), 1, stream);
				fread(&mSOS->mLength, sizeof(short), 1, stream);
				if (mSOS->mLength == (6 + (mSOS->nComp * 2)))
				{
					/* CREATEING COMPONENTS DESCRIPTOR */
					mSOS->comps = (int8_t*) malloc(mSOS->nComp * sizeof(int8_t));
					
					/* Reading [nComp * 2] bytes:	*/
					/* 2 Bytes per component		*/
					fread(&mSOS->comps, sizeof(int8_t), mSOS->nComp * 2, stream);
					/* Reading 3 bytes instead ignoring them	*/
					/* (You never know)							*/
					fread(&mSOS->ignore, sizeof(int8_t), 3, stream);
					
					/* Inserting in JFIF */
					node->marker = mSOS;
					insertMarker(head, tail, *node);
				}
				else
				{
					errNode	= 1;
				}

				/* Image Data immediatly follow SOS Marker,	*/
				/* so we stop the markers scan				*/
				cScan = 0;
				break;
			
			/* Importan */
			case EOI:
			case SOI:
			/* May be ignored */
			case RST0:
			case RST1:
			case RST2:
			case RST3:
			case RST4:
			case RST5:
			case RST6:
			case RST7:
			case TEM:
				insertMarker(head, tail, *node);
				break;
			default:
				printf("UNKNOWN MARKER >> %x\n\n", node->mID.mIdentifier[1] & 0xFF);
				errNode	= 1;
				cScan	= 0;
				break;
			}
		}
	} while (cScan);
	
	/* If marker scanning find an invalide marker, kill the func */
	if (errNode == 1)		
		*head = *tail = NULL;
};

/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************************************************************/

/* Lib funcs */
JFIFIMG readJPEG(const char* filename)
{
	JFIFIMG		img;			/* The image */
	
	rgb_i		pxldata;
	JFIFMARKER*	marker;

	FILE*		f;				/* File Data Stream */

	/* Init img Markers */
	img.mrkH = img.mrkT = NULL;

	/* Apertura file */
	f = fopen(filename, "r");
	/* Uscita in caso di file non trovato */
	if (f == NULL)
		exit(0);
	
	/* READ ALL MARKERS UP TO SOS */
	readMarkers(&img.mrkH, &img.mrkT, f);

	/* TODO >> READ AND DECOMPRESS */

	/* Chiusura file */
	fclose(f);

	return img;
};
/* 23 */