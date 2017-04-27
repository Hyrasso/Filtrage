#include <stdio.h>
#include "bmp.h"


PIXEL** create_tab(int width, int height)
{
    int i;
    PIXEL** im = malloc(sizeof(PIXEL *)*height);
    for (i = 0;i < height;i++)
    {
        im[i] = malloc(sizeof(PIXEL)*width);
    }
    return im;
}
//i : ligne, j : colonne
void set_pixel(PIXEL** image, int i, int j, PIXEL px)
{
    image[i][j] = px;
}
PIXEL get_pixel(PIXEL** image, int i, int j)
{
    return image[i][j];
}
void free_tab(PIXEL** image, int height)
{
    int i;
    for(i = 0;i < height;i++)
    {
        free(image[i]);
    }
    free(image);
}

PIXEL** im_to_tab(PIXEL* src, int width, int height)
{
    PIXEL** tab = create_tab(width, height);
    int x, y;
    for(y=0;y<height;y++)
    {
        for(x=0;x<width;x++)
        {
            set_pixel(tab, x, y, src[(height-1-y)*width+x]);
        }
    }
    return tab;
}

PIXEL* tab_to_im(PIXEL** src, int width, int height)
{
    PIXEL* im = malloc(sizeof(PIXEL)*width*height);
    int x, y;
    for(y=0;y < height;y++)
    {
        for(x=0;x < width;x++)
        {
            im[x+(height-1-y)*width] = get_pixel(src, x, y);
        }
    }
    return im;
}

PIXEL** conv3x3(PIXEL** src,int width, int height, int* k)
{
    PIXEL **res = create_tab(width, height);
    int i, j;
    int di, dj;
    int red, green, blue;
    PIXEL pixel;
    printf("Go ..\n");
    //ignore sides
    for(i=1;i < height-1;i++)
    {
        for(j=1;i < width-1;i++)
        {
            red = 0;
            green = 0;
            blue = 0;
            for(di=0;di < 3;di++)
            {
                for(dj=0;dj < 3;dj++)
                {
                    pixel = get_pixel(src, i+di-1, j+dj-1);
                    blue += (int)pixel.blue * k[di+dj*3];
                    green += (int)pixel.green * k[di+dj*3];
                    red += (int)pixel.red * k[di+dj*3];
                }
            }
            printf("%d, %d\n", (unsigned char)(blue/9), pixel.blue);
            PIXEL new_pixel = {(unsigned char)(blue/9), (unsigned char)(green/9), (unsigned char)(red/9)};
            set_pixel(res, i, j, new_pixel);
        }
    }
    return res;
}

