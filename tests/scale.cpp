#include <dbg.h>
#include <transform.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Usage: run <input_filename> <width> <height> <output_filename>";
		cout << endl << endl;
		return 1;
	}

	Image* image = image_from_file(argv[1]);
	Image* output = image_scale(image, atoi(argv[2]), atoi(argv[3]));
	image_to_file(output, argv[4]);

	free_image(output);
	free_image(image);

	return 0;
}
