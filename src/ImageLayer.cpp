//
// Created by waxta on 24.11.19.
//

#include "ImageLayer.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPen>

ImageLayer::ImageLayer() : drawableList(0)
{
	setFlag(QGraphicsItem::ItemClipsChildrenToShape);
	QPen pen(Qt::NoPen);
	pen.setWidth(5);
}

void ImageLayer::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	for( auto child : childItems() )
	{
		child->paint(painter, option, widget);
	}
}

void ImageLayer::AddDrawableItem(QGraphicsItem* item)
{
	drawableList.push_back(item);
}

QRectF ImageLayer::boundingRect() const
{
	return QRectF(0, 0, width, heigt);
}

ImageLayer::~ImageLayer()
{
}

void ImageLayer::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
}

void ImageLayer::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
}

void ImageLayer::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
}

void ImageLayer::SetSize(qreal width, qreal height)
{
	this->width = width;
	this->heigt = height;
}
