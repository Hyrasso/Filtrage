#include "polygon.h"
#include "segment.h"

void polygon(PIXEL** image, POINT points[], int size, PIXEL color) {
    int i;
    for(i=0;i<size-1;i++) {
        segment_bresenham(image, points[i].x, points[i].y, points[i+1].x, points[i+1].y, color);
    }
    segment_bresenham(image, points[size-1].x, points[size-1].y, points[0].x, points[0].y, color);
}

void polygon_filled(PIXEL** image, POINT points[], int size, PIXEL color) {
    int max_y = 0, min_y = 0;
    int i;
    for(i=1;i<size;i++)  {
        if(points[i].y > points[max_y].y)
            max_y = i;
        if(points[i].y < points[min_y].y)
            min_y = i;
    }
    POINT *lpoints;
    lpoints = malloc(sizeof(*points)+sizeof(int));
    for(i=0;i<size;i++)
        lpoints[i] = points[i];
    lpoints[size] = points[0];

    int y, x;
    int x1, x2, y1, y2;
    float m, c;
    printf("poly between : %d %d\n", points[min_y].y, points[max_y].y);
    for(y=points[min_y].y;y < points[max_y].y;y++) {
        printf("Line %d\n", y);
        int *draw = calloc(size, sizeof(int));
        int nb = 0;
        for(i=0;i<size;i++) {
                x1 = lpoints[i].x;
                x2 = lpoints[i+1].x;
                y1 = lpoints[i].y;
                y2 = lpoints[i+1].y;
                if(x2!=x1) {
                    m = (y2-y1)/(x2-x1);
                    c = y1 - x1*m;
                    x = (y - c)/m;
                }else {
                    x = x1;
                }
                printf("  Intersec at %d (%d, %d, eq:y=%fx+%f)\n", x, x1, x2, m, c);
                if((x < x1 && x > x2) || (x > x1 && x < x2)) {
                    int j;
                    for(j=0;j<nb && x<draw[j];j++);
                    draw[j] = x;
                    nb += 1;
                }
        }
        printf("   points : %d\n", nb);
        for(i=0;i<nb;i+=2)
            printf("  drawing %d, %d\n", draw[i], draw[i+1]);
            segment_bresenham(image, draw[i], y, draw[i+1], y, color);
    }
}
