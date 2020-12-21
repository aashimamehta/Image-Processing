// Program1.cpp
// Author:  Aashima Mehta
// Purpose: Reads a test image (hardcoded to "test.gif"), then
//       modifies an image and saves the image to "output" file and
//       also creates a mirror image of the test1.gif and saves the image to "outputMirror" file.
// Note: one can change "test1.gif" to change the image to the image in .gif format that they want to invert the image to.

#include "ImageLib.h"
#include <iostream>
using namespace std;

// forward declarations
void modified(image in);
void invertPixel(pixel& p, int row, int col);
void mirrorImage(image in);
void comparePixels(image in, image inM);


// main()
// Precondition:   test.gif exists and is a valid GIF image
// Postconditions: output.gif will be written and it will contain
//				   a modified image with blue and red pixels aletered from test1.gif
int main() {
	// Read test image from file and will be modified
	image input = ReadGIF("test1.gif");
	if (input.rows == 0) {
		cout << "Unable to open file: test.gif" << endl;
		return -1;
	}


	//Reads the image form the file to Mirror this image and will be mirrored 
	image inputMirror = ReadGIF("test1.gif");
	if (input.rows == 0) {
		cout << "Unable to open file: test.gif" << endl;
		return -1;
	}

	// Create modified image
	modified(input);
	//Create mirror image
	mirrorImage(inputMirror);

	// Output modified red and blue pixel image, results
	cout << "The dimensions of the image are: " << input.rows << " rows by " << input.cols << " columns." << endl;
	WriteGIF("output.gif", input);
	//Reading the output image results
	image output = ReadGIF("output.gif");


	//Output Mirror image results
	cout << "The dimensions of the image are: " << inputMirror.rows << " rows by " << inputMirror.cols << " columns." << endl;
	WriteGIF("outputMirror.gif", inputMirror);
	//Reading the output image results
	image outputMirror = ReadGIF("outputMirror.gif");

	//Check the pixel differences between the images and print if the images are different
	comparePixels(output, outputMirror);

	// Wait for user input before exiting
	system("PAUSE");
	DeallocateImage(input);
        DeallocateImage(inputMirror);
	DeallocateImage(output);
	DeallocateImage(outputMirror);
	return 0;
}


// modified: modifies the input image to create a modified image with red and blue pixels altered according to their position
// Preconditions: the input image (in) has in.rows * in.cols pixels allocated
// Postconditions: the input image is modified such that all of the pixel colors are changed
void modified(image in) {
	for (int row = 0; row < in.rows; row++) {
		for (int col = 0; col < in.cols; col++) {
			invertPixel(in.pixels[row][col], row, col);
		}
	}
}

// invertPixel: modifies the color of a blue and red pixels
// Preconditions:  None
// Postconditions:  Each color band of the input pixel p has been modifies red and blue 
//                  depending upton their rows and coloumns
//                  Also the function appropriately takes care of over and under flow of pixels.

void invertPixel(pixel& p, int row, int col)
{
	//for blue pixel
	if (p.blue) { //image.pixels[r][c].red
		if ((p.blue - (row % 7)) >= 255) {
			p.blue = 255;
		}
		else if ((p.blue - (row % 7)) <= 0) {
			p.blue = 0;
		}
		else {
			p.blue = p.blue - (row % 7);
		}
	}
	//For the red pixel
	if (p.red) { //myImage.pixels[r][c].red!!!!
		if ((p.red + (col % 7)) >= 255) {
			p.red = 255;
		}
		else if ((p.red + (col % 7)) <= 0) {
			p.red = 0;
		}
		else {
			p.red = p.red + (col % 7);
		}
	}
}

//mirrorImage: mirrors the image
//PreConditions: None
//PostConditions: the image ouput should be the mirror image of "test1.gif" file.
void mirrorImage(image in) {
	for (int col = 0; col < in.cols /2; col++) {
		for (int row = 0; row < in.rows; row++) {
			int temp = in.cols - 1 - col;
			pixel p = in.pixels[row][temp];
			in.pixels[row][temp] = in.pixels[row][col];
			in.pixels[row][col] = p;
		}
	}
}

//comparePixels: will compare the two output images, namely "output" and "outputMirror" files
//PreConditions: the images are altered properly by the functions written above, i.e,
//       one should have modified pixels and the other one should be a mirror image.
//PostCondition: the function will give us an accurate number of different pixels, if there exist any 
//                 differences in the image.
void comparePixels(image in, image inM) {
	int count = 0;
	for (int row = 0; row < in.rows; row++) {
		for (int col = 0; col < in.cols; col++) {
			pixel& p = in.pixels[row][col];
			pixel& pp = inM.pixels[row][col];
			if ((p.red != pp.red) || (p.blue != pp.blue) || (p.green != pp.green) ){
				count++;
			}
		}
	}
	if (count > 0) {
		cout << "The two images have " << count << " number of different pixels." << endl;
	}
	else {
		cout << "Both images are have the same number of pixels." << endl;
	}
}

