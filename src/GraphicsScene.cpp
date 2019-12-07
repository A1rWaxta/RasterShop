//
// Created by waxta on 03.12.19.
//

#include "GraphicsScene.h"
#include <QDebug>

GraphicsScene::GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject* parent) : QGraphicsScene(x, y, width,
                                                                                                            height,
                                                                                                            parent)
{

}

GraphicsScene::GraphicsScene(QObject* parent) : QGraphicsScene(parent), activeLayer(nullptr)
{

}

void GraphicsScene::AddItemOnActiveLayer(QGraphicsItem* item)
{
	item->setParentItem(activeLayer);
}

QString& GraphicsScene::CreateLayer()
{
	QString layerName = "layer_" + QString::number(layers.size());

	auto newLayer = new ImageLayer(layerName);
	newLayer->setZValue(layers.size());
	layers[layerName] = newLayer;
	addItem(newLayer);
	activeLayer = newLayer;

	return newLayer->GetLayerIdentifier();
}

void GraphicsScene::SetActveLayer(ImageLayer* layer)
{
	activeLayer = layer;
}