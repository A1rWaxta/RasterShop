//
// Created by waxta on 16.01.20.
//

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include "GaussianBlur.h"

QImage GaussianBlur::Blur(QImage image)
{
	image.save("tmp_img.png");
	cv::Mat src = cv::imread("tmp_image.png");
	return QImage();
}