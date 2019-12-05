//
// Created by waxta on 24.11.19.
//

#include "ImageLayer.h"

ImageLayer::ImageLayer(QString& layerIdentifier, QGraphicsItem* parent) : QGraphicsItem(parent), drawableList(0)
{
	this->layerIdentifier = layerIdentifier;
}

void ImageLayer::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	for(auto item : drawableList)
	{
		item->paint(painter, option, widget);
	}
}

void ImageLayer::AddDrawableItem(QGraphicsItem* item)
{
	drawableList.push_back(item);
}

QRectF ImageLayer::boundingRect() const
{
	return QRectF();
}

QString& ImageLayer::GetLayerIdentifier()
{
	return layerIdentifier;
}

ImageLayer::~ImageLayer()
{
	for(auto item : drawableList)
	{
		delete item;
	}
}
