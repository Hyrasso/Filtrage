#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

BITMAP * loadBitmapFile(const char *filename)
{
    FILE *pBitmapFile;
    pBitmapFile = fopen(filename,"rb");
    if (pBitmapFile)
    {
        BITMAP *pBitmap = (BITMAP *)malloc(sizeof(BITMAP));
        if (!pBitmap)
        {
            fclose(pBitmapFile);
            return NULL;
        }
        fread(&pBitmap->fileHeader, sizeof(BITMAPFILEHEADER),1,pBitmapFile);
        if (pBitmap->fileHeader.type[0] != 'B' || pBitmap->fileHeader.type[1] != 'M')
        {
            free(pBitmap);
            fclose(pBitmapFile);
            return NULL;
        }
        fread(&pBitmap->infoHeader, sizeof(BITMAPINFOHEADER), 1, pBitmapFile);
        if (pBitmap->infoHeader.colors)
        {
            pBitmap->palette = (RGBQUAD *)malloc(sizeof(RGBQUAD) * pBitmap->infoHeader.colors);
            if (!pBitmap->palette)
            {
                free(pBitmap);
                fclose(pBitmapFile);
                return NULL;
            }
            fread(pBitmap->palette, sizeof(RGBQUAD), pBitmap->infoHeader.colors, pBitmapFile);
        }
        else
            pBitmap->palette = NULL;
        pBitmap->raster = (unsigned char *)malloc(pBitmap->infoHeader.imageSize);
        if (!pBitmap->raster)
        {
            free(pBitmap->palette);
            free(pBitmap);
            fclose(pBitmapFile);
            return NULL;
        }
        fread(pBitmap->raster, pBitmap->infoHeader.imageSize, 1, pBitmapFile);
        fclose(pBitmapFile);
        return pBitmap;
    }
    return NULL;
}

int saveBitmapFile(const char *filename, const BITMAP * const pBitmap)
{
    if (pBitmap && pBitmap->raster)
    {
        FILE *pBitmapFile;
        pBitmapFile = fopen(filename,"wb");
        if (pBitmapFile)
        {
            fwrite(&pBitmap->fileHeader, sizeof(BITMAPFILEHEADER), 1, pBitmapFile);
            fwrite(&pBitmap->infoHeader, sizeof(BITMAPINFOHEADER), 1, pBitmapFile);
            if (pBitmap->infoHeader.colors)
                fwrite(pBitmap->palette, sizeof(RGBQUAD), pBitmap->infoHeader.colors, pBitmapFile);
            fwrite(pBitmap->raster, pBitmap->infoHeader.imageSize, 1, pBitmapFile);
            fclose(pBitmapFile);
            return 1;
        }
    }
    return 0;
}

void destroyBitmapFile(BITMAP * const pBitmap)
{
    if (pBitmap)
    {
        free(pBitmap->palette);
        free(pBitmap->raster);
        free(pBitmap);
    }
}
