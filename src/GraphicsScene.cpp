//
// Created by waxta on 03.12.19.
//

#include "GraphicsScene.h"

GraphicsScene::GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject* parent) : QGraphicsScene(x, y, width,
                                                                                                            height,
                                                                                                            parent)
{

}

QString& GraphicsScene::CreateLayer()
{
	QString layerName = "layer_" + QString(layers.size());
	ImageLayer tmpLayer(layerName, nullptr);
	layers.push_back(tmpLayer);
	addItem(&layers.back());

	return layers.back().GetLayerIdentifier();
}

void GraphicsScene::SetActveLayer(ImageLayer* active)
{
	activeLayer = active;
}


