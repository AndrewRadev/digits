#include <dbg.h>
#include <image.h>
#include <convolution.h>
#include <transform.h>
#include <iostream>

using namespace std;

int image_match(Image* image, Image* template_image) {
	Matrix* template_matrix = image_to_intensity_matrix(template_image);
	Image* output           = image_convolution(image, template_matrix);
	Image* auto_convolution = image_convolution(template_image, template_matrix);
	int max_value           = image_max_intensity(output);
	int max_possible_value  = image_max_intensity(auto_convolution);

	free_image(output);
	free_image(auto_convolution);

	if (max_possible_value > 0) {
		return (max_value * 100) / max_possible_value;
	} else {
		return 0;
	}
}

int check_template(Image* image, Image* template_image) {
	int original_height = image_height(image);
	int new_height      = image_height(template_image);
	int new_width       = -1;
	int max_match_ratio = 0;

	while (new_height <= original_height) {
		new_width = (new_height / (float)image_height(image)) * image_width(image);

		Image* resized_image = image_scale(image, new_width, new_height, 0);
		int match_ratio = image_match(resized_image, template_image);
		// printf("Height: %d, Ratio: %d\n", new_height, match_ratio);

		free_image(resized_image);

		if (max_match_ratio < match_ratio) {
			max_match_ratio = match_ratio;
		}

		new_height += 1;
	}

	return max_match_ratio;
}

int main(int argc, char* argv[])
{
	SetEasyBMPwarningsOff();

	if (argc != 2)
	{
		cout << "Usage: run <input_filename>";
		cout << endl << endl;
		return 1;
	}

	Image* image = image_invert(image_from_file(argv[1]));

	Image* templates[10];
	templates[0] = image_invert(image_from_file("templates/0.bmp"));
	templates[1] = image_invert(image_from_file("templates/1.bmp"));
	templates[2] = image_invert(image_from_file("templates/2.bmp"));
	templates[3] = image_invert(image_from_file("templates/3.bmp"));
	templates[4] = image_invert(image_from_file("templates/4.bmp"));
	templates[5] = image_invert(image_from_file("templates/5.bmp"));
	templates[6] = image_invert(image_from_file("templates/6.bmp"));
	templates[7] = image_invert(image_from_file("templates/7.bmp"));
	templates[8] = image_invert(image_from_file("templates/8.bmp"));
	templates[9] = image_invert(image_from_file("templates/9.bmp"));

	int ratio = 0;

	for (int i = 0; i < 10; i++) {
		printf("Checking for match with %d... ", i);
		ratio = check_template(image, templates[i]);
		printf("%d%%\n", ratio);

		if (ratio == 100) {
			printf("Good match found: %d\n", i);
			return 0;
		}
	}

	for (int i = 0; i < 10; i++) {
		free_image(templates[i]);
	}
	free_image(image);
	return 0;
}
