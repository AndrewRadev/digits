#include <stdlib.h>
#include <easybmp/EasyBMP.h>

typedef BMP Image;

Image* image_from_file(const char *filename);
void free_image(Image* image);
