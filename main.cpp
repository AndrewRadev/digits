#include "src/image.h"
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

	// declare and read the bitmap
	Image* input = image_from_file(argv[1]);

	// convert each pixel to grayscale using RGB->YUV
	for (int j=0; j < input->TellHeight(); j++) {
		for (int i=0; i < input->TellWidth(); i++) {
			int Temp = (int) floor( 0.299*input->operator()(i,j)->Red +
						0.587*input->operator()(i,j)->Green +
						0.114*input->operator()(i,j)->Blue );
			ebmpBYTE TempBYTE = (ebmpBYTE) Temp;
			input->operator()(i,j)->Red   = TempBYTE;
			input->operator()(i,j)->Green = TempBYTE;
			input->operator()(i,j)->Blue  = TempBYTE;
		}
	}

	// Create a grayscale color table if necessary
	if( input->TellBitDepth() < 16 ) {
		CreateGrayscaleColorTable( *input );
	}

	// write the output file
	input->WriteToFile( argv[2] );

	free_image(input);

	return 0;
}
