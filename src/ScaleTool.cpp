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
	normalPen.setColor(Qt::black);
	normalPen.setWidth(2);
	normalPen.setStyle(Qt::SolidLine);
	setPen(normalPen);
	setBrush(Qt::NoBrush);
	pointRectangle.setPen(normalPen);
	pointRectangle.setBrush(Qt::NoBrush);
	setRect(QRectF(0, 0, 0, 0));
	pointRectangle.setRect(QRectF(0, 0, 0, 0));
	pointRectangle.setParentItem(this);

	selectedIndicatorPen.setWidth(2);
	selectedIndicatorPen.setColor(Qt::yellow);
	selectedIndicatorPen.setStyle(Qt::SolidLine);
}

void ScaleTool::SetLayer(ImageLayer* layer)
{
	setRect(layer->boundingRect());
	setPos(layer->pos());
	QPointF topLeft(rect().width() - DISTANCE_FROM_BOTTOM_RIGHT_POINT,
	                rect().height() - DISTANCE_FROM_BOTTOM_RIGHT_POINT);
	QPointF bottomRight(rect().width() + DISTANCE_FROM_BOTTOM_RIGHT_POINT,
	                    rect().height() + DISTANCE_FROM_BOTTOM_RIGHT_POINT);
	QRectF rect(topLeft, bottomRight);
	pointRectangle.setRect(rect);
	this->layer = layer;
}

void ScaleTool::Update(QPointF currentPoint)
{
	qreal currentDistance = std::sqrt(std::pow(rect().topLeft().x() - currentPoint.x(), 2) +
	                                  std::pow(rect().topLeft().y() - currentPoint.y(), 2));
	layer->setScale(currentDistance / startDistance);

	setRect(layer->boundingRect());
	qDebug() << rect().size();
}

void ScaleTool::Start()
{
	startDistance = std::sqrt(std::pow(rect().bottomRight().x() - rect().topLeft().x(), 2) +
	                          std::pow(rect().bottomRight().y() - rect().topLeft().y(), 2));
}

bool ScaleTool::IsPointRectangleSelected(QPointF point)
{
	return pointRectangle.contains(point);
}
