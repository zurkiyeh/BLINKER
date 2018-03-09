#include "stdafx.h"
#include "BlobDetector.h"




int main(int argc, char *argv[]) {

	Point2D coordinates;
	BlobDetector tracker(240, 144);
	tracker.showFrames = true;
	


	ofstream myfile;
	myfile.open("filedata.txt");


	char charCheckForEscKey = 0;

	while (charCheckForEscKey != 27) {
		coordinates = tracker.detect();

		myfile << coordinates.getX() << " " << coordinates.getY() << "\n";
		cout << coordinates.getX() << " " << coordinates.getY() << "\n";
		
		charCheckForEscKey = cv::waitKey(1);
	}
	
	myfile.close();
	cout << "Compiled!" << endl;

	return 0;
}


