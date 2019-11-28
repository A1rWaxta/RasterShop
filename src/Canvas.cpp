//
// Created by waxta on 27.08.19.
//

#include "Canvas.h"
#include <QPainter>
#include <QDebug>

Canvas::Canvas(QWidget *parent, const QPoint &position, const QSize &size,
               unsigned int frameTime) : QWidget(parent)
{
	move(position);
	resize(size);
	timer.setInterval(frameTime);
	setAutoFillBackground(true);

	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_OpaquePaintEvent);
	setAttribute(Qt::WA_NoSystemBackground);

	qDebug() << "tworze canvas";
	connect(&timer, SIGNAL(timeout()), this, SLOT(repaint()));
	timer.start();
}

void Canvas::paintEvent(QPaintEvent *paintEvent)
{
	QPainter painter(this);
	QRectF rect(pos(), size());
	QBrush brush(Qt::yellow, Qt::SolidPattern);
	QPen pen(Qt::PenStyle::NoPen);

	qDebug() << width() << height();

	painter.setPen(pen);
	painter.fillRect(rect, brush);
	painter.drawRect(rect);
}

void Canvas::LoadImage(QString &fileName)
{
	//pixmap.load(fileName);
}