#include <stdlib.h>
#include <easybmp/EasyBMP.h>

typedef BMP Image;
typedef RGBApixel Pixel;
typedef ebmpBYTE Byte;

Image *image_from_file(const char *filename);
void free_image(Image* image);

int image_height(Image* image);
int image_width(Image* image);
Pixel &image_get_pixel(Image* image, int i, int j);

void ensure_grayscale_color_table(Image* image);
void image_to_file(Image* image, const char* filename);
