#pragma once

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

#include "point2D.h"


using std::cout; using  std::endl; using std::cerr;
using namespace std;
using namespace cv;
using namespace std::chrono;


class BlobDetector
{
public:

	BlobDetector(int width, int height);
	~BlobDetector();
	Point2D detect();
	void initializeParam();
	bool showFrames;
	
	cv::VideoCapture webcam;
	cv::Mat imgOriginal;        // input image
	cv::Mat imgGrayscale;       // grayscale of input image
								//cv::Mat imgBlurred;         // intermediate blured image
								//cv::Mat imgCanny;           // Canny edge image
	cv::Mat keypoints;

	// Setup SimpleBlobDetector parameters.
	SimpleBlobDetector::Params params;

};

