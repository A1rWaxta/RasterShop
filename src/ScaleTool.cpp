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
	setRect(layer->mappedToSceneBoundingRect());
	QPointF topLeft(layer->mappedToSceneBoundingRect().bottomRight().x() - DISTANCE_FROM_BOTTOM_RIGHT_POINT,
	                layer->mappedToSceneBoundingRect().bottomRight().y() + DISTANCE_FROM_BOTTOM_RIGHT_POINT);
	QPointF bottomRight(layer->mappedToSceneBoundingRect().bottomRight().x() + DISTANCE_FROM_BOTTOM_RIGHT_POINT,
	                layer->mappedToSceneBoundingRect().bottomRight().y() - DISTANCE_FROM_BOTTOM_RIGHT_POINT);
	QRectF rect(topLeft, bottomRight);
	pointRectangle.setRect(rect);
}

void ScaleTool::Update(QPointF currentPoint)
{
	qreal currentDistance = std::sqrt(std::pow(layer->transformOriginPoint().x() - currentPoint.x(), 2) +
	                                  std::pow(layer->transformOriginPoint().y() - currentPoint.y(), 2));
	layer->setScale(currentDistance / startDistance);

	QPointF topLeft(layer->mappedToSceneBoundingRect().bottomRight().x() - DISTANCE_FROM_BOTTOM_RIGHT_POINT,
	                layer->mappedToSceneBoundingRect().bottomRight().y() + DISTANCE_FROM_BOTTOM_RIGHT_POINT);
	QPointF bottomRight(layer->mappedToSceneBoundingRect().bottomRight().x() + DISTANCE_FROM_BOTTOM_RIGHT_POINT,
	                    layer->mappedToSceneBoundingRect().bottomRight().y() - DISTANCE_FROM_BOTTOM_RIGHT_POINT);
	QRectF rect(topLeft, bottomRight);
	pointRectangle.setRect(rect);

	setRect(layer->mappedToSceneBoundingRect());
}

void ScaleTool::Start()
{
	startDistance = std::sqrt(std::pow(rect().bottomRight().x() - layer->transformOriginPoint().x(), 2) +
	                          std::pow(rect().bottomRight().y() - layer->transformOriginPoint().y(), 2));
}

bool ScaleTool::IsPointRectangleSelected(QPointF point)
{
	return pointRectangle.boundingRect().contains(point);
}

void ScaleTool::Stop()
{

}
