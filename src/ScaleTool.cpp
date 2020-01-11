//
// Created by waxta on 09.01.20.
//

#include <QtGui/QPen>
#include "ScaleTool.h"
#include <QDebug>
#include <cmath>

namespace
{
	constexpr auto DISTANCE_FROM_BOTTOM_RIGHT_POINT = 8;
}

ScaleTool::ScaleTool() : layer(nullptr)
{
	setPen(QPen(Qt::black, 2, Qt::SolidLine));
	setBrush(Qt::NoBrush);
	pointRectangle.setBrush(Qt::NoBrush);
	setRect(QRectF(0, 0, 0, 0));
	pointRectangle.setRect(QRectF(0, 0, 0, 0));
	pointRectangle.setParentItem(this);

	pointRectangle.setPen(QPen(Qt::green, 2, Qt::SolidLine));
}

void ScaleTool::SetLayer(ImageLayer* layer)
{
	this->layer = layer;
	setRect(layer->boundingRect());
	QPointF topLeft(layer->boundingRect().bottomRight().x() - DISTANCE_FROM_BOTTOM_RIGHT_POINT,
	                layer->boundingRect().bottomRight().y() + DISTANCE_FROM_BOTTOM_RIGHT_POINT);
	QPointF bottomRight(layer->boundingRect().bottomRight().x() + DISTANCE_FROM_BOTTOM_RIGHT_POINT,
	                layer->boundingRect().bottomRight().y() - DISTANCE_FROM_BOTTOM_RIGHT_POINT);
	QRectF rect(topLeft, bottomRight);
	pointRectangle.setRect(rect);
}

void ScaleTool::Update(QPointF currentPoint)
{
	qreal currentDistance = std::sqrt(std::pow(rect().topLeft().x() - currentPoint.x(), 2) +
	                                  std::pow(rect().topLeft().y() - currentPoint.y(), 2));
	layer->setScale(currentDistance / startDistance);

	QPointF topLeft(layer->boundingRect().bottomRight().x() - DISTANCE_FROM_BOTTOM_RIGHT_POINT,
	                layer->boundingRect().bottomRight().y() + DISTANCE_FROM_BOTTOM_RIGHT_POINT);
	QPointF bottomRight(layer->boundingRect().bottomRight().x() + DISTANCE_FROM_BOTTOM_RIGHT_POINT,
	                    layer->boundingRect().bottomRight().y() - DISTANCE_FROM_BOTTOM_RIGHT_POINT);
	QRectF rect(topLeft, bottomRight);
	pointRectangle.setRect(rect);

	setRect(layer->boundingRect());
}

void ScaleTool::Start()
{
	startDistance = std::sqrt(std::pow(rect().bottomRight().x() - rect().topLeft().x(), 2) +
	                          std::pow(rect().bottomRight().y() - rect().topLeft().y(), 2));
}

bool ScaleTool::IsPointRectangleSelected(QPointF point)
{
	return pointRectangle.boundingRect().contains(point);
}
