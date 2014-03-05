#pragma once

#include <opencv2/core/core.hpp>

extern cv::Scalar bgr2hsv(cv::Scalar &color_bgr);
extern cv::Scalar hsv2bgr(cv::Scalar &color_hsv);
extern void draw_text(cv::Mat &img, const char *msg, const int x, const int y);


