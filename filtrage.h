#ifndef FILTRAGE
#define FILTRAGE
PIXEL** create_tab(PIXEL* src, int width, int height);
void set_pixel(PIXEL** image, int i, int j, PIXEL px);
void free_tab(PIXEL** image, int height);
PIXEL** conv3x3(PIXEL* src,int width, int height, int* k);
PIXEL** im_to_tab(PIXEL* src, int width, int height);
PIXEL* tab_to_im(PIXEL** src, int width, int height);

#endif // FILTRAGE

