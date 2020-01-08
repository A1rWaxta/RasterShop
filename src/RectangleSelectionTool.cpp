//
// Created by waxta on 08.01.20.
//

#include <QtGui/QPen>
#include "RectangleSelectionTool.h"
#include <QDebug>

RectangleSelectionTool::RectangleSelectionTool()
{
	QPen pen;
	pen.setColor(Qt::yellow);
	pen.setWidthF(2);
	pen.setStyle(Qt::DashLine);
	setPen(pen);
	setBrush(Qt::NoBrush);
}

void RectangleSelectionTool::Start(QPointF pos)
{
	startPoint = pos;
	selectionArea.setWidth(0);
	selectionArea.setHeight(0);
	setRect(selectionArea);
}

void RectangleSelectionTool::Update(QPointF currentPoint)
{
	if( currentPoint.x() > startPoint.x() and currentPoint.y() > startPoint.y() )
	{
		selectionArea.setBottomLeft(startPoint);
		selectionArea.setTopRight(currentPoint);
	}
	else if( currentPoint.x() < startPoint.x() and currentPoint.y() > startPoint.y() )
	{
		selectionArea.setBottomRight(startPoint);
		selectionArea.setTopLeft(currentPoint);
	}
	else if( currentPoint.x() < startPoint.x() and currentPoint.y() < startPoint.y() )
	{
		selectionArea.setTopRight(startPoint);
		selectionArea.setBottomLeft(currentPoint);
	}
	else if( currentPoint.x() > startPoint.x() and currentPoint.y() < startPoint.y() )
	{
		selectionArea.setTopLeft(startPoint);
		selectionArea.setBottomRight(currentPoint);
	}
	prepareGeometryChange();
	setRect(selectionArea);
}

QRectF RectangleSelectionTool::GetSelectedRegion()
{
	return selectionArea;
}
