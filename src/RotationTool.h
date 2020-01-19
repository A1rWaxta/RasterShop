//
// Created by waxta on 10.01.20.
//

#pragma once

#include <QtWidgets/QGraphicsRectItem>
#include "ImageLayer.h"

class RotationTool : public QGraphicsRectItem
{
public:
	RotationTool();
	void Start(QPointF startPoint);
	void Update(QPointF currentPoint);
	void Stop();
	void SetLayer(ImageLayer* layer);

private:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	ImageLayer* layer;
	QPointF startPoint;
	QGraphicsEllipseItem ellipseItem;
	bool leftMousePressed;
};