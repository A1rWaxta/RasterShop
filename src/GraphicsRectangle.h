//
// Created by waxta on 03.12.19.
//

#pragma once

#include <QtWidgets/QGraphicsRectItem>

class GraphicsRectangle : public QGraphicsRectItem
{
public:
	explicit GraphicsRectangle(QGraphicsItem* parent = nullptr);

	GraphicsRectangle(const QRectF& rect, QGraphicsItem* parent);

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

};


