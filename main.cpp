#include <dbg.h>
#include <image.h>
#include <image_template.h>
#include <convolution.h>
#include <transform.h>
#include <trim.h>
#include <iostream>

using namespace std;

int image_match(Image* image, ImageTemplate* image_template) {
	Image* output           = image_convolution(image, image_template->matrix);
	Image* auto_convolution = image_convolution(image_template->image, image_template->matrix);
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

int check_template(Image* image, ImageTemplate* image_template) {
	Image* trimmed_image = image_trim(image, 0);
	Image* resized_image = image_scale(trimmed_image, image_width(image_template->image), image_height(image_template->image), 0);
	int match_ratio = image_match(resized_image, image_template);

	free_image(resized_image);
	free_image(trimmed_image);

	return match_ratio;
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

	ImageTemplate* templates[10];
	templates[0] = new_image_template(0, "templates/0.bmp", 80);
	templates[1] = new_image_template(0, "templates/1.bmp", 80);
	templates[2] = new_image_template(0, "templates/2.bmp", 80);
	templates[3] = new_image_template(0, "templates/3.bmp", 80);
	templates[4] = new_image_template(0, "templates/4.bmp", 80);
	templates[5] = new_image_template(0, "templates/5.bmp", 80);
	templates[6] = new_image_template(0, "templates/6.bmp", 80);
	templates[7] = new_image_template(0, "templates/7.bmp", 80);
	templates[8] = new_image_template(0, "templates/8.bmp", 80);
	templates[9] = new_image_template(0, "templates/9.bmp", 80);

	int ratio = 0;
	int max_ratio = -1;
	ImageTemplate* max_template = NULL;

	for (int i = 0; i < 10; i++) {
		printf("Checking for match with %d... ", i);
		ratio = check_template(image, templates[i]);
		printf("%d%%\n", ratio);

		if (ratio >= templates[i]->threshold) {
			print_image_match(templates[i], ratio);
			return 0;
		}

		if (max_ratio <= ratio) {
			max_ratio = ratio;
			max_template = templates[i];
		}
	}

	print_image_match(max_template, max_ratio);

	for (int i = 0; i < 10; i++) {
		free_image_template(templates[i]);
	}
	free_image(image);
	return 0;
}
