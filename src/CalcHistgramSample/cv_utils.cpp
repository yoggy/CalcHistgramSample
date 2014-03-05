#include "cv_utils.h"
#include <opencv2/imgproc/imgproc.hpp>

#define max2(a, b) (a > b ? a : b)
#define min2(a, b) (a < b ? a : b)
#define min3(a, b, c) (min2(a, min2(b, c)))
#define max3(a, b, c) (max2(a, max2(b, c)))

cv::Scalar bgr2hsv(cv::Scalar &color_bgr)
{
	cv::Scalar color_hsv;
	double r, g, b, h, s, v;

	r = color_bgr.val[2] / 255.0f;
	g = color_bgr.val[1] / 255.0f;
	b = color_bgr.val[0] / 255.0f;

	double max = max3(r, g, b);
	double min = min3(r, g, b);

	v = max;

	if (max == 0.0f) {
		s = 0;
		h = 0;
	}
	else if (max - min == 0.0f) {
		s = 0;
		h = 0;
	}
	else {
		s = (max - min) / max;

		if (max == r) {
			h = 60 * ((g - b) / (max - min)) + 0;
		}
		else if (max == g) {
			h = 60 * ((b - r) / (max - min)) + 120;
		}
		else {
			h = 60 * ((r - g) / (max - min)) + 240;
		}
	}

	if (h < 0) h += 360.0f;

	color_hsv.val[0] = h / 2.0f;  // h:0-180 (for OpenCV HSV)
	color_hsv.val[1] = s * 255; 
	color_hsv.val[2] = v * 255;

	return color_hsv;
}

cv::Scalar hsv2bgr(cv::Scalar &color_hsv)
{
	cv::Scalar color_bgr;
	double r, g, b, h, s, v;

	h = color_hsv.val[0] * 2.0f; // h:0-360
	s = color_hsv.val[1] / 255.0f;
	v = color_hsv.val[2] / 255.0f;

	int hi = (int)(h / 60.0f) % 6;
	double f = (h / 60.0f) - hi;
	double p = v * (1.0f - s);
	double q = v * (1.0f - s * f);
	double t = v * (1.0f - s * (1.0f - f));

	switch(hi) {
	case 0:
		r = v;
		g = t;
		b = p;
		break;
	case 1:
		r = q;
		g = v;
		b = p;
		break;
	case 2:
		r = p;
		g = v;
		b = t;
		break;
	case 3:
		r = p;
		g = q;
		b = v;
		break;
	case 4:
		r = t;
		g = p;
		b = v;
		break;
	case 5:
		r = v;
		g = p;
		b = q;
		break;
	}
	color_bgr.val[2] = r * 255;
	color_bgr.val[1] = g * 255;
	color_bgr.val[0] = b * 255;

	return color_bgr;
}

void draw_text(cv::Mat &img, const char *msg, const int x, const int y)
{
	int face = cv::FONT_HERSHEY_PLAIN;
	float scale = 1.0f;
	int w = 2;

	for (int dy = -w; dy <= w; ++dy) {
		for (int dx = -w; dx <= w; ++dx) {
			cv::putText(img, msg, cv::Point(x+dx, y+dy), face, scale, CV_RGB(0,0,0));
		}
	}
	cv::putText(img, msg, cv::Point(x, y), face, scale, CV_RGB(255,255,255));
}
