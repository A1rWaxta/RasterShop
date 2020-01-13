//
// Created by waxta on 24.11.19.
//

#pragma once


#include <QtCore/QVector>
#include "ImageLayer.h"
#include "WorkSpace.h"

class Canvas : public QGraphicsRectItem
{
public:
	Canvas(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent = nullptr);
	void CreateLayer(QColor &color);
	QRectF boundingRect() const override;

private:

};