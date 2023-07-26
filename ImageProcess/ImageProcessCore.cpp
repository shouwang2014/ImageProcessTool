#include "ImageProcessCore.h"

cv::Mat LoadImage(const std::string& filepath)
{
	CV_Assert(!filepath.empty());

	cv::Mat _img = cv::imread(filepath);

	return _img;
}