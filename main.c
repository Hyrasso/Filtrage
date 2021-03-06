#include <stdio.h>
#include "bmp.h"
#include "filtrage.h"
#include "functions.h"
#include "segment.h"
#include "polygon.h"

#define N 3

int main(void)
{
    PIXEL white = {255, 255, 255};
    PIXEL blue = {255, 0, 0};
    PIXEL red = {0, 0, 255};
    PIXEL green = {0, 255, 0};

    POINT points[N] = {{10, 10},
                    {100, 10},
                    {10, 100}};

    /*
    POINT points[N] = { {173, 71},
                        {206, 56},
                        {69, 196},
                        {79, 149},
                        {58, 70},
                        {109, 19}};
    */
    BITMAP * lenaBitmap = loadBitmapFile(".\\images\\lena_256_color.bmp");
    if (lenaBitmap->infoHeader.bits == 24 && !lenaBitmap->palette)
    {
        PIXEL * image = (PIXEL *)lenaBitmap->raster;
        const unsigned int size = lenaBitmap->infoHeader.height * lenaBitmap->infoHeader.width;
        const unsigned int width = lenaBitmap->infoHeader.width;
        const unsigned int height = lenaBitmap->infoHeader.height;

        PIXEL **tab;
        tab = im_to_tab(image, width, height);
        polygon_filled(tab, points, N, red);
        /*
        tab = sobel(tab, width, height);

        segment_bresenham(tab, 0, 0, 255, 125, green);//1
        segment_bresenham(tab, 0, 0, 125, 255, green);//2

        segment_bresenham(tab, 255, 0, 125, 255, white);//3
        segment_bresenham(tab, 255, 0, 0, 125, white);//4

        segment_bresenham(tab, 255, 255, 0, 125, blue);//5
        segment_bresenham(tab, 255, 255, 125, 0, blue);//6

        segment_bresenham(tab, 0, 255, 125, 0, red);//7
        segment_bresenham(tab, 0, 255, 255, 125, red);//8
        */
        image = tab_to_im(tab, width, height);
        free_tab(tab, height);
        lenaBitmap->raster = image;

    }

    if (lenaBitmap)
    {
        saveBitmapFile(".\\images\\lena_polygonefill.bmp", lenaBitmap);
        destroyBitmapFile(lenaBitmap);
        printf("Done.\n");
    }
    else
        printf("Echec.\n");
    return 0;
}
