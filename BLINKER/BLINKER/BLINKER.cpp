#include "stdafx.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "features2d.hpp"
#include <chrono>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <iostream>
#include<conio.h>           // may have to modify this line if not using Windows

using std::cout; using  std::endl;
using namespace std;
using namespace cv;
using namespace std::chrono;

///////////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	cv::VideoCapture capWebcam(0);            // declare a VideoCapture object and associate to webcam, 0 => use 1st webcam
	capWebcam.set(cv::CAP_PROP_FRAME_WIDTH, 240); // valueX = your wanted width
	capWebcam.set(cv::CAP_PROP_FRAME_HEIGHT, 144); // valueY = your wanted heigth
	if (capWebcam.isOpened() == false)

	{                                // check if VideoCapture object was associated to webcam successfully
									 //		std::cout << "error: capWebcam not accessed successfully\n\n";      // if not, print error message to std out
		_getch();                                                           // may have to modify this line if not using Windows
		return(0);                                                          // and exit program
	}

	cv::Mat imgOriginal;        // input image
	cv::Mat imgGrayscale;       // grayscale of input image
								//cv::Mat imgBlurred;         // intermediate blured image
								//cv::Mat imgCanny;           // Canny edge image
	cv::Mat keypoints;

	char charCheckForEscKey = 0;

	while (charCheckForEscKey != 27 && capWebcam.isOpened())
	{            // until the Esc key is pressed or webcam connection is lost
		bool blnFrameReadSuccessfully = capWebcam.read(imgOriginal);            // get next frame

		if (!blnFrameReadSuccessfully || imgOriginal.empty())
		{                 // if frame not read successfully
						  //			std::cout << "error: frame not read from webcam\n";                 // print error message to std out
			break;                                                              // and jump out of while loop
		}

		cv::cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);                   // convert to grayscale

																				//cv::GaussianBlur(imgGrayscale,              // input image
																				//	imgGrayscale,                // output image
																				//	cv::Size(9, 9),            // smoothing window width and height in pixels
																				//	2, 2);                      // sigma value, determines how much the image will be blurred

																				// Set threshold and maxValue for binary converison
		double thresh = 100;
		double maxValue = 255;

		// Binary Threshold
		//threshold(imgGrayscale, imgGrayscale, thresh, maxValue, THRESH_BINARY);

		// Setup SimpleBlobDetector parameters.
		SimpleBlobDetector::Params params;

		// Change thresholds
		params.minThreshold = 100;
		params.maxThreshold = 200;

		// Filter by Area.
		params.filterByArea = true;
		params.minArea = 100;

		// Filter by Circularity
		params.filterByCircularity = true;
		params.minCircularity = 0.1;

		// Filter by Convexity
		params.filterByConvexity = true;
		params.minConvexity = 0.87;

		// Filter by Inertia
		params.filterByInertia = true;
		params.minInertiaRatio = 0.01;




#if CV_MAJOR_VERSION < 3   // If you are using OpenCV 2

		// Set up detector with params
		SimpleBlobDetector detector(params);

		// You can use the detector this way
		// detector.detect( im, keypoints);

#else

		// Set up detector with params
		Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

		// SimpleBlobDetector::create creates a smart pointer. 
		// So you need to use arrow ( ->) instead of dot ( . )
		// detector->detect( im, keypoints);

#endif

		// Detect blobs.
		std::vector<KeyPoint> keypoints;
		detector->detect(imgGrayscale, keypoints);

		// Draw detected blobs as red circles.
		// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
		Mat im_with_keypoints;
		drawKeypoints(imgGrayscale, keypoints, im_with_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

		// @Error
		if (keypoints.empty()) {
			cout << "Vector is empty";

		}
		else {
			Point2f point1 = keypoints.at(0).pt;
			float x1 = point1.x;
			float y1 = point1.y;

		}
		float x1 = 0;
		float y1 = 0;




		//string filename[1] = { "filedata.txt" };
		//outputFile[i].open(filename[i].c_str());
		ofstream myfile;
		myfile.open("filedata.txt");
		myfile << x1 << " " << y1 << "\n";
		myfile.close();
		cout << x1 << " " << y1 << "\n";




		// Show blobs
		cv::imshow("keypoints", im_with_keypoints);
		//waitKey(0);

		high_resolution_clock::time_point t1 = high_resolution_clock::now();

		// declare windows
		//    cv::namedWindow("imgOriginal", CV_WINDOW_NORMAL);       // note: you can use CV_WINDOW_NORMAL which allows resizing the window
		//cv::namedWindow("imgGrayscale", CV_WINDOW_NORMAL);          // or CV_WINDOW_AUTOSIZE for a fixed size window matching the resolution of the image													// CV_WINDOW_AUTOSIZE is the default
		//	cv::imshow("imgOriginal", imgOriginal);                 // show windows
		//cv::imshow("imgGrayscale", imgGrayscale);                       //

		charCheckForEscKey = cv::waitKey(1);        // delay (in ms) and get key press, if any
	}   // end while

	return(0);
}