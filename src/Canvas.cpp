//
// Created by waxta on 27.08.19.
//

#include "Canvas.h"
#include <QPainter>
#include <QPaintEvent>

#ifdef DEBUG

#include <QDebug>

#endif

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
	QString layerName = "layer_" + QString(layers.size());
	ImageLayer tmpLayer(layerName, nullptr);
	layers.push_back(tmpLayer);

	return layers.back().GetLayerIdentifier();
}

void Canvas::AddItem(QGraphicsItem* item)
{
	//todo: ustawić activeLayer !!!!!!
	item->setParentItem(activeLayer);
	scene()->addItem(item);
}