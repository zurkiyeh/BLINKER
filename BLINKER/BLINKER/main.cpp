#include "stdafx.h"
#include "BlobDetector.h"




int main(int argc, char *argv[]) {

	BlobDetector tracker(240, 144);
	tracker.showFrames = true;
	while (true) {
		tracker.detect();

	}
	
	cout << "Compiled!" << endl;

	return 0;
}


