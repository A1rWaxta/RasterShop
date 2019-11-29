//
// Created by waxta on 24.11.19.
//

#include "ImageLayer.h"

ImageLayer::ImageLayer(int width, int height, QColor & color) : QImage(width, height, QImage::Format_ARGB32)
{

}

ImageLayer::ImageLayer(const QImage &image) : QImage(image)
{

}
