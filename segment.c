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
    //https://fr.wikipedia.org/wiki/Algorithme_de_trac%C3%A9_de_segment_de_Bresenham#Algorithme_g.C3.A9n.C3.A9ral_optimis.C3.A9
    int dx = x2 - x1, dy = y2 - y1;
    if(dx != 0) {
        if(dx > 0) {
            if(dy != 0) {
                if(dy > 0) {
                    if(dx >= dy) {
                        int e = dx ;
                        dx = e * 2 ;
                        dy = dy * 2 ;  // e est positif
                        while(1) {  // déplacements horizontaux
                          set_pixel(image, x1, y1, color) ;
                          x1 = x1 + 1;
                          if(x1 == x2) break ;
                          e = e - dy;
                          if(e < 0) {
                            y1 = y1 + 1 ;  // déplacement diagonal
                            e = e + dx ;
                          }
                        }
                    } else {
                    // vecteur oblique proche de la verticale, dans le 2d octant
                        int e = dy;
                        dy = e * 2 ;
                        dx = dx * 2 ;  // e est positif
                        while(1) {  // déplacements verticaux
                          set_pixel(image, x1, y1, color) ;
                          y1 = y1 + 1;
                          if(y1 == y2) break;
                          e = e - dx;
                          if(e < 0) {
                            x1 = x1 + 1 ;  // déplacement diagonal
                            e = e + dy ;
                          }
                        }
                    }

            } else {  // dy < 0 (et dx > 0)
              // vecteur oblique dans le 4e cadran

              if(dx >= -dy) {
                // vecteur diagonal ou oblique proche de l’horizontale, dans le 8e octant
                int e = dx;
                dx = e * 2 ; dy = dy * 2 ;  // e est positif
                while(1) {  // déplacements horizontaux
                  set_pixel(image, x1, y1, color) ;
                  x1 = x1 + 1;
                  if(x1 == x2) break;
                  e = e + dy;
                  if(e < 0) {
                    y1 = y1 - 1 ;  // déplacement diagonal
                    e = e + dx ;
                  }
                }
              } else {// vecteur oblique proche de la verticale, dans le 7e octant
                int e = dy;
                dy = e * 2 ;
                dx = dx * 2 ;  // e est négatif
                while(1) {  // déplacements verticaux
                  set_pixel(image, x1, y1, color);
                  y1 = y1 - 1;
                  if(y1 == y2) break;
                  e = e + dx;
                  if(e > 0) {
                    x1 = x1 + 1 ;  // déplacement diagonal
                    e = e + dy ;
                  }
                }
              }

            }
          } else { // dy = 0 (et dx > 0)

            // vecteur horizontal vers la droite
            do {
              set_pixel(image, x1, y1, color) ;
              x1 = x1 + 1;
            }while(x1 == x2);

          }
        } else { // dx < 0
          if(dy != 0) {
            if(dy > 0) {
              // vecteur oblique dans le 2d quadran

              if(-dx >= dy) {
                // vecteur diagonal ou oblique proche de l’horizontale, dans le 4e octant
                int e = dx;
                dx = e * 2 ;
                dy = dy * 2 ;  // e est négatif
                while(1) {  // déplacements horizontaux
                  set_pixel(image, x1, y1, color) ;
                  x1 = x1 - 1;
                  if(x1 == x2) break;
                  e = e + dy;
                  if(e >= 0) {
                    y1 = y1 + 1 ;  // déplacement diagonal
                    e = e + dx ;
                  }
                }
              } else {
                // vecteur oblique proche de la verticale, dans le 3e octant
                int e = dy;
                dy = e * 2 ;
                dx = dx * 2 ;  // e est positif
                while(1) {  // déplacements verticaux
                  set_pixel(image, x1, y1, color) ;
                  y1 = y1 + 1;
                  if(y1 == y2) break;
                  e = e + dx;
                  if(e <= 0) {
                    x1 = x1 - 1 ;  // déplacement diagonal
                    e = e + dy ;
                  }
                }
              }

            } else  {// dy < 0 (et dx < 0)
              // vecteur oblique dans le 3e cadran

              if(dx <= dy) {
                // vecteur diagonal ou oblique proche de l’horizontale, dans le 5e octant
                int e = dx;
                dx = e * 2 ;
                dy = dy * 2 ;  // e est négatif
                while(1) {  // déplacements horizontaux
                  set_pixel(image, x1, y1, color) ;
                  x1 = x1 - 1;
                  if(x1 == x2) break;
                  e = e - dy;
                  if(e >= 0) {
                    y1 = y1 - 1 ;  // déplacement diagonal
                    e = e + dx ;
                  }
                }
              } else { // vecteur oblique proche de la verticale, dans le 6e octant
                int e = dy;
                dy = e * 2 ;
                dx = dx * 2 ;  // e est négatif
                while(1) {  // déplacements verticaux
                  set_pixel(image, x1, y1, color) ;
                  y1 = y1 - 1;
                  if(y1 == y2) break;
                  e = e - dx;
                  if(e >= 0) {
                    x1 = x1 - 1 ;  // déplacement diagonal
                    e = e + dy ;
                  }
                }
              }

            }
          } else { // dy = 0 (et dx < 0)

            // vecteur horizontal vers la gauche
            do {
              set_pixel(image, x1, y1, color) ;
              x1 = x1 - 1;
            }while(x1 == x2) ;

          }
        }
      } else {// dx = 0
        if(dy != 0) {
          if(dy > 0) {

            // vecteur vertical croissant
            do {
              set_pixel(image, x1, y1, color) ;
              y1 = y1 + 1;
            }while(y1 == y2) ;

          } else  {// dy < 0 (et dx = 0)

            // vecteur vertical décroissant
            do {
              set_pixel(image, x1, y1, color) ;
              y1 = y1 - 1;
            }while(y1 == y2);

          }
        }
      }
      // le pixel final (x2, y2) n’est pas tracé.
}
