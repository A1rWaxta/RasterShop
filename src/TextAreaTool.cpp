//
// Created by waxta on 12.01.20.
//

#include "TextAreaTool.h"
#include <QPen>

TextAreaTool::TextAreaTool() : textTool(nullptr)
{
	setPen(QPen(Qt::darkGray, 2, Qt::SolidLine));
	setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemClipsChildrenToShape);
	textTool.setParentItem(this);
}

void TextAreaTool::Start(QPointF point)
{
	startPoint = point;
	selectionArea.setWidth(0);
	selectionArea.setHeight(0);
	setRect(selectionArea);
}

void TextAreaTool::Update(QPointF currentPoint)
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

void TextAreaTool::Stop()
{
	textTool.setTextWidth(selectionArea.width());
}

void TextAreaTool::keyPressEvent(QKeyEvent* event)
{
	QGraphicsItem::keyPressEvent(event);
}

void TextAreaTool::SetLayer(ImageLayer* layer)
{
	this->layer = layer;
}
