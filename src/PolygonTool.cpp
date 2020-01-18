//
// Created by waxta on 17.01.20.
//

#include "PolygonTool.h"
#include <QPen>
#include <QDebug>

QRectF PolygonTool::boundingRect() const
{
	QRectF bounding;
	for( auto child : childItems() )
	{
		bounding = bounding.united(child->boundingRect());
	}
	return bounding;
}

void PolygonTool::AddPoint(QPointF point)
{
	points.push_back(point);
	if( points.size() > 1 )
	{
		AddLine(points[points.size() - 2], point);
	}
}

void PolygonTool::AddLine(const QPointF& point1, const QPointF& point2)
{
	QLineF line(point1, point2);
	auto graphicsLine = new QGraphicsLineItem(line);
	graphicsLine->setPen(QPen(Qt::yellow, 2, Qt::DashLine));
	graphicsLine->setParentItem(this);
	lines.push_back(graphicsLine);
}

void PolygonTool::Clear()
{
	points.clear();
	for( auto line : lines )
	{
		delete line;
	}
	lines.clear();
	update();
}

void PolygonTool::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

}

void PolygonTool::Close()
{
	AddPoint(points[0]);
}

int PolygonTool::NumberOfPoints()
{
	return points.size();
}

QPolygonF PolygonTool::GetPolygon()
{
	QPolygonF polygon(QVector<QPointF>::fromStdVector(points));

	if( polygon.isClosed() )
	{
		return polygon;
	}
	else
	{
		return QPolygonF();
	}
}

void PolygonTool::DeleteLastPoint()
{
	if( points.size() > 0 )
	{
		points.pop_back();
		if(lines.size() > 1)
		{
			delete lines.back();
			lines.pop_back();
		}
	}
}
