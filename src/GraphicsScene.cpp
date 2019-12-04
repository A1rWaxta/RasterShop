//
// Created by waxta on 03.12.19.
//

#include "GraphicsScene.h"

GraphicsScene::GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject* parent) : QGraphicsScene(x, y, width,
                                                                                                            height,
                                                                                                            parent)
{

}

void GraphicsScene::CreateBackground(QColor& backgroundColor)
{
	background.setRect(QRectF(0, 0, width(), height()));
	background.setBrush(backgroundColor);
	addItem(&background);
}
