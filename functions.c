#include "bmp.h"
#include <stdio.h>

void miroir(PIXEL * image, unsigned int width, unsigned int height) {
    PIXEL tmp;
    int mx, x, y;
    for (x = 0;x < width / 2;x++) {
        for (y = 0;y < height;y++) {
            mx = (width - 1) - x;
            tmp = image[y * width + mx];
            image[y * width + mx] = image[y * width + x];
            image[y * width + x] = tmp;
        }
    }

}

void miroirdiag(PIXEL * image, unsigned int width, unsigned int height) {
    PIXEL tmp;
    int mx, my, y, x;
    for (y = 0;y < height;y++) {
        for (x = 0;x < height - y;x++) {
            mx = (width - 1) - y;
            my = (height - 1) - x;
            tmp = image[my * width + mx];
            image[my * width + mx] = image[y * width + x];
            image[y * width + x] = tmp;
        }
    }
}

void rot90(PIXEL * image, unsigned int width, unsigned int height) {
    miroirdiag(image, width, height);
    miroir(image, width, height);
}

void greyscale(PIXEL * image, unsigned int size) {
    PIXEL c;
    int i;
    for (i = 0; i < size;i++) {
        c = image[i];
        image[i].blue = (c.red + c.blue + c.green)/3;
        image[i].red = (c.red + c.blue + c.green)/3;
        image[i].green = (c.red + c.blue + c.green)/3;
    }
}
