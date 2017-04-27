#ifndef BMP
#define BMP

#pragma pack(push, 1)  // Modifie l'alignement à 1 octet

typedef struct
{
    char type[2]; // Le nombre magique correspondant à l'utilisation du fichier Bitmap (BMP), pour nous ce sera 'BM' le format de windows.
    unsigned int size; // Taille du fichier en octets.
    unsigned short int reserved1; // Réservé pour l'identifiant de l'application qui a créé le fichier.
    unsigned short int reserved2; // Réservé pour l'identifiant de l'application qui a créé le fichier.
    unsigned int offset; // L'offset (l'adresse de départ) du contenu, c'est-à-dire l'image.
}BITMAPFILEHEADER;

typedef struct
{
    unsigned int size; // Taille en octets de cet en-tête BITMAPINFOHEADER.
    unsigned int width; // Largeur de l’image en pixels.
    unsigned int height; // Hauteur de l’image en pixels.
    unsigned short int planes; // Nombre de plans couleurs.
    unsigned short int bits; // Nombre de bits par pixel.
    unsigned int compression; // Type de compression : 0 pour pas de compression, 1 pour compressé à 8 bits par pixel, 2 pour 4 bits par pixel.
    unsigned int imageSize; // Taille en octets des données de l’image.
    unsigned int xResolution; // Résolution horizontale en pixels par mètre.
    unsigned int yResolution;// Résolution verticale en pixels par mètre.
    unsigned int colors; // Nombre de couleurs dans l’image : 0 pour le maximum  possible. Si une palette est utilisée, ce nombre indique le nombre de couleurs de la palette.
    unsigned int importantColors; // Nombre de couleurs importantes, 0 signifie que toutes importantes.
}BITMAPINFOHEADER;

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char reserved;
}RGBQUAD;

typedef struct
{
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    RGBQUAD *palette;
    unsigned char *raster;
}BITMAP;

typedef struct
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
}PIXEL;

#pragma pack(pop)   // Supprime l'alignement à 1 octet et revient au précédent alignement

BITMAP * loadBitmapFile(const char *filename);
int saveBitmapFile(const char *filename, const BITMAP * const pBitmap);
void destroyBitmapFile(BITMAP * const pBitmap);

#endif // BMP

