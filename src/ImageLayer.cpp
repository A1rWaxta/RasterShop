//
// Created by waxta on 24.11.19.
//

#include "ImageLayer.h"

ImageLayer::ImageLayer(QString& identifier) : drawableList(0)
{
	layerIdentifier = identifier;
}

void ImageLayer::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	for(auto child : childItems())
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
	return QRectF(0, 0, 150, 150);
}

QString& ImageLayer::GetIdentifier()
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

void ImageLayer::SetLayerIdentifier(const QString& identifier)
{
	layerIdentifier = identifier;
}
