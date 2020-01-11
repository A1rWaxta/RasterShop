//
// Created by waxta on 11.01.20.
//

#include "TextTool.h"

TextTool::TextTool() : layer(nullptr)
{

}

void TextTool::SetLayer(ImageLayer* layer)
{

}

void TextTool::Start(QPointF point)
{
	setTextWidth(layer->boundingRect().left() - point.x());
}
