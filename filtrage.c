#include <stdio.h>
#include <math.h>
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
    image[j][i]= px;
}

PIXEL get_pixel(PIXEL** image, int i, int j)
{
    return image[j][i];
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

PIXEL** conv3x3(PIXEL** src, int width, int height, int* kernel)
{
    PIXEL **res = create_tab(width, height);
    int i, j, k;
    int di, dj;
    PIXEL pixel;
    int red, green, blue;
    //ignore sides
    for(j=1;j < height-1;j++)
    {
        for(i=1;i < width-1;i++)
        {
            red = 0;
            green = 0;
            blue = 0;
            for(di=0;di < 3;di++)
            {
                for(dj=0;dj < 3;dj++)
                {
                    pixel = get_pixel(src, i+di-1, j+dj-1);
                    k = kernel[dj+di*3];
                    blue += (int)pixel.blue * k;
                    green += (int)pixel.green * k;
                    red += (int)pixel.red * k;
                }
            }
            PIXEL new_pixel = {(unsigned char)abs(blue/9), (unsigned char)abs(green/9), (unsigned char)abs(red/9)};
            set_pixel(res, i, j, new_pixel);
        }
    }
    return res;
}

PIXEL** sobel(PIXEL** src, int width, int height)
{
    int kx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    PIXEL** gx;
    int ky[9] = {-1, -2, -1, 0, 0, 0, 1, 2 ,1};
    PIXEL** gy;
    int i, j;
    PIXEL x, y;
    gx = conv3x3(src, width, height, kx);
    gy = conv3x3(src, width, height, ky);
    for(j=0;j < height;j++)
    {
        for(i=0;i < width;i++)
        {
            x = get_pixel(gx, i, j);
            y = get_pixel(gy, i, j);
            x.red = (unsigned char)sqrt(pow((double)x.red, 2) + pow((double)y.red, 2));
            x.blue = (unsigned char)sqrt(pow((double)x.blue, 2) + pow((double)y.blue, 2));
            x.green = (unsigned char)sqrt(pow((double)x.green, 2) + pow((double)y.green, 2));
            set_pixel(gx, i, j, x);
        }
    }
    return gx;
}
