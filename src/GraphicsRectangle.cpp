//
// Created by waxta on 03.12.19.
//

#include "GraphicsRectangle.h"
#include <QPainter>

GraphicsRectangle::GraphicsRectangle(const QRectF& rect, QGraphicsItem* parent) : QGraphicsRectItem(rect, parent)
{

}

void GraphicsRectangle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->fillRect(boundingRect(), brush().color());
}

GraphicsRectangle::GraphicsRectangle(QGraphicsItem* parent) : QGraphicsRectItem(parent)
{

}
