//
// Created by waxta on 08.01.20.
//

#pragma once


#include <QtWidgets/QGraphicsRectItem>

class RectangleSelectionTool : public QGraphicsRectItem
{
public:
	RectangleSelectionTool();
	void Start(QPointF pos);
	void Update(QPointF currentPoint);
	QRectF GetSelectedRegion();

private:
	QRectF selectionArea;
	QPointF startPoint;
};


