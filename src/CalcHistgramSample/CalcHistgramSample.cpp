#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "cv_utils.h"

#ifdef WIN32
	#if _DEBUG
		#pragma comment(lib, "opencv_core248d.lib")
		#pragma comment(lib, "opencv_imgproc248d.lib")
		#pragma comment(lib, "opencv_highgui248d.lib")
	#else
		#pragma comment(lib, "opencv_core248.lib")
		#pragma comment(lib, "opencv_imgproc248.lib")
		#pragma comment(lib, "opencv_highgui248.lib")
	#endif
#endif

int main(int argc, char* argv[])
{
	cv::VideoCapture capture;
	if (!capture.open(0)) {
		printf("error : capture.open() failed...\n");
		return -1;
	}

	cv::Mat capture_img;
	capture >> capture_img;

	int capture_w = capture_img.cols;
	int capture_h = capture_img.rows;

	int w = 100;
	cv::Mat rgb_img;
	cv::Mat hsv_img;

	while(true) {
		capture >> capture_img;

		// crop image
		cv::Rect roi(capture_w/2 - w/2, capture_h/2 - w/2, w, w);
		capture_img(roi).copyTo(rgb_img);

		// RGB->HSV
		cv::cvtColor(rgb_img, hsv_img, CV_BGR2HSV);

		// calc H histgram
		cv::Mat hist;
		const int channels[]   = {0};       // channnel0 only
		const int hdims[]      = {180};     // H is 0-179
		const float hranges[]  = {0,179};    
		const float* ranges[]  = {hranges};
		double max_h_val;
		cv::calcHist(&hsv_img, 1, channels, cv::Mat(), hist, 1, hdims, ranges);
		cv::minMaxLoc(hist, 0, &max_h_val);

		// debug draw
		cv::Mat canvas;
		capture_img.copyTo(canvas);

		cv::rectangle(canvas, roi, CV_RGB(0,255,0),2);

		for (int h = 0; h < 180; ++h) {
			double v = hist.at<float>(h) / max_h_val; // 0.0-1.0;
			cv::Scalar c = hsv2bgr(cv::Scalar(h, 255, 255));
			cv::line(canvas, cv::Point(h, 100), cv::Point(h, 100 - (int)(100 * v)), c, 1);
		}
		draw_text(canvas, "[H histgram]", 5, 15);

		cv::imshow("rgb_img", rgb_img);
		cv::imshow("canvas", canvas);

		int c = cv::waitKey(1);
		if (c == 27) break;
	}

	cv::destroyAllWindows();
	return 0;
}

