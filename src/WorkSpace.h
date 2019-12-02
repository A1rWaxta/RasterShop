//
// Created by waxta on 24.11.19.
//

#pragma once


#include <QtCore/QVector>
#include "ImageLayer.h"
#include "Canvas.h"

class WorkSpace
{
public:
	WorkSpace();

	void CreateLayer(QColor &color);

private:
	std::vector<ImageLayer*> layers;

	Canvas * canvas;
};


