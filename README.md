CalcHistgramSample
========

* ![screen shot](http://farm8.staticflickr.com/7384/12946906224_a22170efd4_n.jpg)

<pre>
	// RGB->HSV
	cv::cvtColor(rgb_img, hsv_img, CV_BGR2HSV);

	// calc H histgram
	cv::Mat hist;
	const int channels[] = {0}; // channnel0 only
	const int hdims[] = {180}; // H is 0-179
	const float hranges[] = {0,179};
	const float* ranges[] = {hranges};
	double max_h_val;
	cv::calcHist(&hsv_img, 1, channels, cv::Mat(), hist, 1, hdims, ranges);
	cv::minMaxLoc(hist, 0, &max_h_val);
</pre>
