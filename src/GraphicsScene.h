//
// Created by waxta on 03.12.19.
//

#pragma once

#include <QtWidgets/QGraphicsScene>
#include <QPainter>
#include <QGraphicsRectItem>
#include "GraphicsRectangle.h"
#include "ImageLayer.h"

class GraphicsScene : public QGraphicsScene
{
public:
	GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject* parent = nullptr);

	QString& CreateLayer();

	void SetActveLayer(ImageLayer * active);

private:
	QPainter painter;

	ImageLayer * activeLayer;

	GraphicsRectangle background;
};


