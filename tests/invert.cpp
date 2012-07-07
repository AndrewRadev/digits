#include <dbg.h>
#include <image.h>
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
	image_invert(image);
	image_to_file(image, argv[2]);
	free_image(image);

	return 0;
}
