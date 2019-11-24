//
// Created by waxta on 24.11.19.
//

#include "WorkSpace.h"

WorkSpace::WorkSpace()
{

}

void WorkSpace::CreateLayer(QColor & color)
{
	layers.emplace_back(ImageLayer(canvas->width(), canvas->height(), color));

}
