#include "bmp.h"
#include "filtrage.h"

#define sign(x) ((x>0)?1:((x<0)?-1:0))

void tracer_Segment_0(PIXEL** image, int x1, int y1, int x2, int y2, PIXEL color) {
    int x, y, dx, dy, i;
    float m;
    dx = x2 - x1;
    dy = y2 - y1;
    m = (float)dy/(float)dx;
    for(i = 0; i < dx;i++) {
        x = x1 + i;
        y = (int)(x1 + i * m + .5);
        set_pixel(image, x, y, color);
    }
}

void tracer_Segment_1(PIXEL** image, int x1, int y1, int x2, int y2, PIXEL color) {
    int x, dx, dy;
    float m, y;
    dx = x2 - x1;
    dy = y2 - y1;
    m = (float)dy/(float)dx;
    y = y1;
    for(x = x1; x <= x2;x++) {
        set_pixel(image, x, (int)(y + .5), color);
        y += m;
    }
}

void tracer_Segment_2(PIXEL** image, int x1, int y1, int x2, int y2, PIXEL color) {
    int x, y, dx, dy;
    float e;
    dx = x2 - x1;
    dy = y2 - y1;
    e = 0;
    y = y1;
    x = x1;
    while(x < x2) {
        set_pixel(image, x, y, color);
        e += dy;
        if(2 * e >= dx) {
            y += 1;
            e -= dx;
        }
        x += 1;
    }
}

void segment_bresenham(PIXEL** image, int x1, int y1, int x2, int y2, PIXEL color)
{
    int x, y, dx, dy, sx, sy, p;
    int swap = 0;
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    sx = sign(x2 - x1);
    sy = sign(y1 - y1);
    if(dx < dy)
    {
        dx = dy + dx;
        dy = dx - dy;
        dx = dx - dy;
        swap = 1;
    }
    p = 2 * dy - dx;
    y = y1;
    x = x1;
    int i;
    for(i=1;i<=dx;i++) {
        set_pixel(image, x, y, color);
        while(p >=0) {
            if(swap) {
                x += sx;
            } else {
                y += sy;
                p -= - 2 * dx;
            }
        }
        if(swap)
            y += sy;
        else
            x += sx;
        p += 2 * dy;
    }
}
