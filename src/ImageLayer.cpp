//
// Created by waxta on 24.11.19.
//

#include "ImageLayer.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPen>

ImageLayer::ImageLayer(qreal width, qreal height) : drawableList(0)
{
	QGraphicsRectItem::setFlag(QGraphicsItem::ItemClipsChildrenToShape);
	QGraphicsRectItem::setFlag(QGraphicsItem::ItemIsFocusable);

	setRect(QRectF(0, 0, width, height));
}

void ImageLayer::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	for( auto child : QGraphicsRectItem::childItems() )
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
	return mapRectToScene(rect());
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

void ImageLayer::focusInEvent(QFocusEvent* event)
{
}