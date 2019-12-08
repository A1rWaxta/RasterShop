//
// Created by waxta on 03.12.19.
//

#include "GraphicsScene.h"
#include <QDebug>

GraphicsScene::GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject* parent) : QGraphicsScene(x, y, width,
                                                                                                            height,
                                                                                                            parent),
                                                                                             activeLayer(nullptr)
{
	auto backgroundRectangle = new QGraphicsRectItem(0, 0, width, height);
	backgroundRectangle->setPen(QPen(Qt::SolidLine));
	backgroundRectangle->setBrush(QBrush(QColor(0, 0, 0)));
	addItem(backgroundRectangle);
}

GraphicsScene::GraphicsScene(QObject* parent) : QGraphicsScene(parent), activeLayer(nullptr)
{

}

void GraphicsScene::SetActiveLayer(ImageLayer* layer)
{
	activeLayer = layer;
}

void GraphicsScene::AddItemOnActiveLayer(QGraphicsItem* item)
{
	item->setParentItem(activeLayer);
}