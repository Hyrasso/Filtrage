#ifndef SEGMENT
#define SEGMENT
#include "bmp.h"
void tracer_Segment_0(PIXEL** image, int x1, int y1, int x2, int y2, PIXEL color);
void tracer_Segment_1(PIXEL** image, int x1, int y1, int x2, int y2, PIXEL color);
void tracer_Segment_2(PIXEL** image, int x1, int y1, int x2, int y2, PIXEL color);
void segment_bresenham(PIXEL** image, int x1, int y1, int x2, int y2, PIXEL color);
#endif // SEGMENT
