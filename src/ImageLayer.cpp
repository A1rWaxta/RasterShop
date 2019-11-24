//
// Created by waxta on 24.11.19.
//

#include "ImageLayer.h"

ImageLayer::ImageLayer(int width, int height, QColor & color) : image(width, height, QImage::Format_ARGB32)
{
	image.fill(color);
}

const QImage &ImageLayer::GetImage() const
{
	return image;
}
