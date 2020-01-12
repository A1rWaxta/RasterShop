//
// Created by waxta on 12.01.20.
//

#pragma once


#include <QtWidgets/QGraphicsRectItem>
#include "ImageLayer.h"
#include "TextTool.h"

class TextAreaTool : public QGraphicsRectItem
{
public:
	TextAreaTool();
	void Start(QPointF point);
	void Update(QPointF currentPoint);
	void Stop();
	void SetLayer(ImageLayer* layer);

private:
	void keyPressEvent(QKeyEvent* event) override;
	ImageLayer* layer;
	TextTool textTool;
	QRectF selectionArea;
	QPointF startPoint;
};


