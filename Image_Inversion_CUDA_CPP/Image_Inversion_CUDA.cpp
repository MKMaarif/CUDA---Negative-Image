// This Program is Written by Abubakr Shafique (abubakr.shafique@gmail.com)
#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <chrono>

#include "Inversion_CUDA.h"

using namespace std;
using namespace cv;
using namespace std::chrono;

int main() {
	Mat Input_Image = imread("Test_Image.png");
	Mat Input_Image2 = imread("Test_Image.png");

	cout << "Height: " << Input_Image.rows << ", Width: " << Input_Image.cols << ", Channels: " << Input_Image.channels() << endl;

	// Get starting timepoint
	auto start2 = high_resolution_clock::now();

	Image_Inversion_CUDA(Input_Image2.data, Input_Image2.rows, Input_Image2.cols, Input_Image2.channels());

	// Get ending timepoint
	auto stop2 = high_resolution_clock::now();

	// Get duration. Substart timepoints to
	// get duration. To cast it to proper unit
	// use duration cast method
	auto duration2 = duration_cast<microseconds>(stop2 - start2);

	cout << "GPU Time : "
		<< duration2.count() << " microseconds" << endl;

	// Menampilkan negative image
	imshow("Negative Image GPU", Input_Image2);

	// Get starting timepoint
	auto start = high_resolution_clock::now();

	// Membuat negative image
	Mat negImg(Input_Image.rows, Input_Image.cols, CV_8UC3, Scalar(0, 0, 0));
	for (int y = 0; y < Input_Image.rows; y++)
	{
		for (int x = 0; x < Input_Image.cols; x++)
		{
			negImg.at<Vec3b>(y, x)[0] = 255 - Input_Image.at<Vec3b>(y, x)[0];
			negImg.at<Vec3b>(y, x)[1] = 255 - Input_Image.at<Vec3b>(y, x)[1];
			negImg.at<Vec3b>(y, x)[2] = 255 - Input_Image.at<Vec3b>(y, x)[2];
		}
	}

	// Get ending timepoint
	auto stop = high_resolution_clock::now();

	// Get duration. Substart timepoints to
	// get duration. To cast it to proper unit
	// use duration cast method
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "CPU Time : "
		<< duration.count() << " microseconds" << endl;

	// Menampilkan negative image
	// namedWindow("Negative Image", WINDOW_AUTOSIZE);
	imshow("Negative Image CPU", negImg);

	waitKey(0);
	system("pause");
	return 0;
}

void Image_Inversion_CPU() {
	
}