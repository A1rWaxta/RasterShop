//
// Created by waxta on 17.01.20.
//

#pragma once


#include <QtWidgets/QGraphicsItem>

class PolygonTool : public QGraphicsObject
{
	Q_OBJECT

public:
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	void AddPoint(QPointF point);
	void Close();
	void Clear();
	int NumberOfPoints();
	QPolygonF GetPolygon();

private:
	void AddLine(const QPointF& point1, const QPointF& point2);
	std::vector<QPointF> points;
	std::vector<QGraphicsLineItem*> lines;
};


