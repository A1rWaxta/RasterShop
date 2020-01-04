//
// Created by waxta on 24.11.19.
//

#include "ImageLayer.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPen>

ImageLayer::ImageLayer(QString& identifier): identifier(identifier)
{
	setFlag(QGraphicsItem::ItemIsSelectable);
	setFlag(QGraphicsItem::ItemIsMovable);
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

QRectF ImageLayer::boundingRect() const
{
	QRectF boundingRect;
	for( auto child : childItems() )
	{
		boundingRect = boundingRect.united(child->boundingRect());
	}
	return boundingRect;
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

void ImageLayer::SetLayerIdentifier(QString& identifier)
{
	this->identifier = identifier;
}

QString& ImageLayer::GetLayerIdentifier()
{
	return identifier;
}
