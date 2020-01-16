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
	void Start(QPointF point);
	void SetLayer(ImageLayer* layer);

private:
	void keyPressEvent(QKeyEvent* event) override;
	void focusInEvent(QFocusEvent* event) override;
	void focusOutEvent(QFocusEvent* event) override;
	QGraphicsRectItem boundingRectangle;
	bool leftMousePressed;
	ImageLayer* layer;
};


