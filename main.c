#include <stdio.h>
#include "bmp.h"
#include "filtrage.h"

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
        //const unsigned int size = lenaBitmap->infoHeader.height * lenaBitmap->infoHeader.width;
        const unsigned int width = lenaBitmap->infoHeader.width;
        const unsigned int height = lenaBitmap->infoHeader.height;

        int kernel[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
        PIXEL **tab;
        tab = im_to_tab(image, width, height);
        tab = conv3x3(tab, width, height, kernel);
        image = tab_to_im(tab, width, height);
        free_tab(tab, height);
        lenaBitmap->raster = image;
    }

    if (lenaBitmap)
    {
        saveBitmapFile(".\\images\\lena_kernelI.bmp", lenaBitmap);
        destroyBitmapFile(lenaBitmap);
        printf("Bye bye Lena.\n");
    }
    else
        printf("Echec.\n");
    return 0;
}
