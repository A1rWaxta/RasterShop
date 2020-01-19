//
// Created by waxta on 09.01.20.
//

#pragma once

#include <QtWidgets/QGraphicsRectItem>
#include "ImageLayer.h"

class ScaleTool : public QGraphicsRectItem
{
public:
	ScaleTool();
	void Update(QPointF currentPoint);
	void SetLayer(ImageLayer* layer);
	void Start();
	void Stop();
	bool IsPointRectangleSelected(QPointF point);

private:
	ImageLayer* layer;
	QGraphicsRectItem pointRectangle;
	qreal startDistance;
};


