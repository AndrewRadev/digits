#include <dbg.h>
#include <image.h>
#include <matrix.h>
#include <grayscale.h>
#include <convolution.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Usage: run <input_filename> <template_filename> <output_image>";
		cout << endl << endl;
		return 1;
	}

	Image* image          = image_from_file(argv[1]);
	Image* template_image = image_from_file(argv[2]);

	image_invert(image);
	image_invert(template_image);

	Matrix* template_matrix = image_to_intensity_matrix(template_image);
	Image* output = image_convolution(image, template_matrix);
	Image* auto_convolution = image_convolution(template_image, template_matrix);

	int max_value = image_max_intensity(output);
	int max_possible_value = image_max_intensity(auto_convolution);

	printf("Max value: %d\n", max_value);
	printf("Max possible value: %d\n", max_possible_value);
	printf("Ratio: %d%\n", (max_value * 100) / max_possible_value);

	image_to_file(output, argv[3]);

	free_image(output);
	free_matrix(template_matrix);
	free_image(template_image);
	free_image(image);

	return 0;
}
