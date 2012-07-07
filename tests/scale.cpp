#include <dbg.h>
#include <transform.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Usage: run <input_filename> <output_filename>";
		cout << endl << endl;
		return 1;
	}

	Image* image = image_from_file(argv[1]);
	Image* output = image_scale(image, 83, 100);
	image_to_file(output, argv[2]);

	free_image(output);
	free_image(image);

	return 0;
}
