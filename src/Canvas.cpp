//
// Created by waxta on 24.11.19.
//

#include "Canvas.h"
#include <QDebug>

Canvas::Canvas(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent)
		: QGraphicsRectItem(x, y, w, h, parent)
{
	setPen(Qt::NoPen);
	setBrush(QBrush(Qt::gray));
	setFlag(QGraphicsItem::ItemClipsChildrenToShape);
	setFlag(QGraphicsItem::ItemIsSelectable);
	setSelected(true);
}

void Canvas::CreateLayer(QColor & color)
{
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent* releaseMouseEvent)
{
	qDebug() << "XD";
}
