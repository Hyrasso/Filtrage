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
            set_pixel(tab, x, y, src[y*width+x]);
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
            im[x+y*width] = src[y][x];
        }
    }
    return im;
}

PIXEL** conv3x3(PIXEL* src,int width, int height, int* k)
{
    PIXEL** res = create_tab(width, height);
    int x, y;
    int dx, dy;
    int red, green, blue;
    PIXEL p;
    for(y=1;y < height-1;y++)
    {
        for(x=1;x < width-1;x++)
        {
            red = 0;
            green = 0;
            blue = 0;
            for(dx=0;dx < 3;dx++)
            {
                for(dy=0;dy < 3;dy++)
                {
                    p = src[(y+dy)*width+(x+dx)];
                    blue += (int)p.blue * k[dx+dy*3];
                    green += (int)p.green * k[dx+dy*3];
                    red += (int)p.red * k[dx+dy*3];
                }
            }
            PIXEL np = {(char)(blue/9), (char)(green/9), (char)(red/9)};
            set_pixel(res, y, x, np);
        }
    }
    return res;
}

