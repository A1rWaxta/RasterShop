//
// Created by waxta on 10.01.20.
//

#include "RotationTool.h"
#include <QtGui/QPen>
#include <QDebug>
#include <cmath>

namespace
{
	constexpr auto DISTANCE_FROM_MID_POINT = 8;
}

RotationTool::RotationTool() : layer(nullptr)
{
	setPen(QPen(Qt::black, 2, Qt::SolidLine));
	ellipseItem.setRect(QRectF(0, 0, 0, 0));
	ellipseItem.setBrush(Qt::NoBrush);
	ellipseItem.setPen(QPen(Qt::green, 2, Qt::SolidLine));
//	ellipseItem.setParentItem(this);
}

void RotationTool::Start(QPointF startPoint)
{
	this->startPoint = startPoint;
}

void RotationTool::Update(QPointF currentPoint)
{
	layer->setRotation(startPoint.y() - currentPoint.y());

	setRect(layer->boundingRect());
}

void RotationTool::Stop()
{
}

void RotationTool::SetLayer(ImageLayer* layer)
{
	this->layer = layer;
	setRect(layer->boundingRect());
	QPointF topLeft((layer->boundingRect().bottomRight().x() / 2) - DISTANCE_FROM_MID_POINT,
	                (layer->boundingRect().bottomRight().y() / 2) + DISTANCE_FROM_MID_POINT);
	QPointF bottomRight((layer->boundingRect().bottomRight().x() / 2) + DISTANCE_FROM_MID_POINT,
	                    (layer->boundingRect().bottomRight().y() / 2) - DISTANCE_FROM_MID_POINT);
	QRectF rect(topLeft, bottomRight);

	ellipseItem.setRect(rect);
}
