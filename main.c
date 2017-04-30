#include <stdio.h>
#include "bmp.h"
#include "filtrage.h"
#include "functions.h"

int main(void)
{
    /*
    PIXEL blanc = {255, 255, 255};
    PIXEL bleu = {255, 0, 0};
    PIXEL rouge = {0, 0, 255};
    PIXEL vert = {0, 255, 0};
    */


    BITMAP * lenaBitmap = loadBitmapFile(".\\images\\lena_256_color.bmp");
    if (lenaBitmap->infoHeader.bits == 24 && !lenaBitmap->palette)
    {
        PIXEL * image = (PIXEL *)lenaBitmap->raster;
        const unsigned int size = lenaBitmap->infoHeader.height * lenaBitmap->infoHeader.width;
        const unsigned int width = lenaBitmap->infoHeader.width;
        const unsigned int height = lenaBitmap->infoHeader.height;

        int kernel[9] = {-1, -2, -1, 0, 0, 0, 1, 2 ,1};
        PIXEL **tab;
        greyscale(image, size);
        tab = im_to_tab(image, width, height);
        tab = sobel(tab, width, height);
        image = tab_to_im(tab, width, height);
        free_tab(tab, height);
        lenaBitmap->raster = image;
    }

    if (lenaBitmap)
    {
        saveBitmapFile(".\\images\\lena_kernelSobel.bmp", lenaBitmap);
        destroyBitmapFile(lenaBitmap);
        printf("Bye bye Lena.\n");
    }
    else
        printf("Echec.\n");
    return 0;
}
