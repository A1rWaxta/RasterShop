//
// Created by waxta on 24.11.19.
//

#include "ImageLayer.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

ImageLayer::ImageLayer() : drawableList(0)
{
}

void ImageLayer::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	for( auto child : childItems())
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
	QRectF boundingRect;
	for( auto child : childItems())
	{
		boundingRect = boundingRect.united(child->boundingRect());
	}
	return boundingRect;
}

ImageLayer::~ImageLayer()
{
}

void ImageLayer::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    	if( mouseEvent->button() == Qt::LeftButton )
	{
		if( contains(mouseEvent->pos()) == true )
		{
		}
		mouseLeftButtonPressed = true;
	}
}

void ImageLayer::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if( mouseEvent->button() == Qt::LeftButton
		and
		sceneBoundingRect().contains(mouseEvent->scenePos())
		)
	{
		qDebug() << "inside item";
		mouseLeftButtonPressed = false;
	}
}
