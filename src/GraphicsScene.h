//
// Created by waxta on 03.12.19.
//

#pragma once

#include <QtWidgets/QGraphicsScene>
#include <QPainter>
#include <QGraphicsRectItem>
#include "GraphicsRectangle.h"
#include "ImageLayer.h"

class MainWindow;

class GraphicsScene : public QGraphicsScene
{
Q_OBJECT

	friend MainWindow;

public:
	GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject* parent = nullptr);

	explicit GraphicsScene(QObject* parent);

private slots:


signals:
	//void QS

private:
	void SetActiveLayer(ImageLayer* layer);

	void AddItemOnActiveLayer(QGraphicsItem* item);

	ImageLayer* activeLayer;
};