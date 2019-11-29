//
// Created by waxta on 24.11.19.
//

#pragma once


#include <QtGui/QImage>

class ImageLayer : public QImage
{
public:
	explicit ImageLayer(int width, int height, QColor &color);
	explicit ImageLayer(const QImage & image);

private:


};


