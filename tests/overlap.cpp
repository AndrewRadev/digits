#include <image.h>
#include <util.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Usage: run <first_input_filename> <second_input_filename>";
		cout << endl << endl;
		return 1;
	}

	Image* first  = image_from_file(argv[1]);
	Image* second = image_from_file(argv[2]);

	debug_image_overlap(first, second, "debug.bmp");

	free_image(second);
	free_image(first);

	return 0;
}
