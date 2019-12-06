//
// Created by waxta on 27.08.19.
//

#include "Canvas.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>


Canvas::Canvas(QWidget* parent)
{
}

void Canvas::LoadImage(QString& fileName)
{
}

Canvas::~Canvas()
{
}

void Canvas::SetRenderAreaSize(QSize size)
{
	setMinimumWidth(size.width() + 200);
	setMinimumHeight(size.height() + 200);

	const int centerY = width() / 2 - size.width() / 2;
	const int centerX = height() / 2 - size.height() / 2;
	renderArea = QRect(QPoint(centerY, centerX), size);
}

QString& Canvas::CreateLayer()
{
	QString layerName = "layer_" + QString::number(layers.size());

	auto newLayer = new ImageLayer(layerName);
	layers.push_back(newLayer);
	scene()->addItem(newLayer);
	activeLayer = newLayer;

	return newLayer->GetLayerIdentifier();
}

void Canvas::AddItem(QGraphicsItem* item)
{
	item->setParentItem(activeLayer);
}