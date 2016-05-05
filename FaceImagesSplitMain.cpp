#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include <opencv.hpp>
#include <dlib/opencv.h>

using namespace cv;
using namespace dlib;
using namespace std;

int main(int argc, char** argv) try
{
	if (argc != 4)
	{
		cout << "Call this program like this: " << endl;
		cout << "./ERT.exe ../ImagesPath ../ImagesHaveFacePath ../ImagesHaveNoFacePath" << endl;
		return 1;
	}

	frontal_face_detector face_detector = get_frontal_face_detector();

	// Get the list of video frames.  
	std::vector<file> files = get_files_in_directory_tree(argv[1], match_ending(".jpg"));
	std::sort(files.begin(), files.end());
	if (files.size() == 0)
	{
		cout << "No images found in " << argv[1] << endl;
		return 1;
	}
	int imagenum = 1000000000;
	for (unsigned long i = 1; i < files.size(); ++i)
	{
		cout << files[i] << endl;
		Mat frame = imread(files[i]);

		if (frame.empty())
		{
			continue;
		}
		if (frame.channels()==4)
		{
			cvtColor(frame, frame, CV_BGRA2BGR);
		}
		dlib::cv_image<bgr_pixel> image = frame;

		std::vector<dlib::rectangle> dets = face_detector(image);

		if (dets.size()!=0)
		{
			char imagepath[128];
			strcpy(imagepath, argv[2]);
			char strnum[32];
			itoa(imagenum++, strnum,10);
			strcat(imagepath, strnum);
			strcat(imagepath, ".jpg");
			imwrite(imagepath, frame);
		}
		else
		{
			char imagepath[128];
			strcpy(imagepath, argv[3]);
			char strnum[32];
			itoa(imagenum++, strnum, 10);
			strcat(imagepath, strnum);
			strcat(imagepath, ".jpg");
			imwrite(imagepath, frame);
		}
	}

	return 0;
}

catch (std::exception& e)
{
	cout << e.what() << endl;
}