#include "bmp.h"

#ifndef POLYGON
#define POLYGON

typedef struct POINT{
    int x, y;
}POINT;

void polygon(PIXEL** image, POINT points[], int size, PIXEL color);
void polygon_filled(PIXEL** image, POINT points[], int size, PIXEL color);
#endif // POLYGON

