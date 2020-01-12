//
// Created by waxta on 11.01.20.
//

#pragma once


#include <QtWidgets/QGraphicsTextItem>
#include "ImageLayer.h"

class TextTool : public QGraphicsTextItem
{
public:
	TextTool();
	void SetLayer(ImageLayer* layer);
	void Start(QPointF point);

private:
	void keyPressEvent(QKeyEvent* event) override;
	void focusInEvent(QFocusEvent* event) override;
	ImageLayer* layer;
};


