//
// Created by waxta on 27.08.19.
//

#include "Canvas.h"
#include <QPainter>

Canvas::Canvas(QWidget *parent, const QPoint &position, const QSize &size, unsigned int frameTime) :
	QWidget(parent)
{
	move(position);
	resize(size);
	timer.setInterval(frameTime);

//	setAttribute(Qt::WA_PaintOnScreen);
//	setAttribute(Qt::WA_OpaquePaintEvent);
//	setAttribute(Qt::WA_NoSystemBackground);

	connect(&timer, SIGNAL(timeout()), this, SLOT(repaint()));
	timer.start();
}

void Canvas::paintEvent(QPaintEvent *paintEvent)
{
	QPainter painter(this);
	QRectF rect(pos(), size());
	QBrush brush(Qt::red, Qt::SolidPattern);
	QPen pen(Qt::PenStyle::NoPen);
	QPixmap pixmap;

	pixmap.load("/home/waxta/Documents/Programming/C++/RasterShop/test-image.png");
	painter.setPen(pen);
	painter.fillRect(rect, brush);
	painter.drawRect(rect);
	painter.drawPixmap(pos(), pixmap);
}