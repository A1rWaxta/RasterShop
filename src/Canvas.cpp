//
// Created by waxta on 27.08.19.
//

#include "Canvas.h"
#include <QPainter>
#include <QDebug>
#include <QPaintEvent>

Canvas::Canvas(QWidget *parent, const QPoint &position, const QSize &size,
               unsigned int frameTime) : QWidget(parent), image(nullptr)
{
	move(position);
	resize(size);

	QImage tmpImage(size, QImage::Format_ARGB32);
	tmpImage.fill(Qt::red);
	layers.push_back(new ImageLayer(tmpImage));
//	image = new QImage(tmpImage);

//	setAttribute(Qt::WA_PaintOnScreen);
//	setAttribute(Qt::WA_OpaquePaintEvent);

	qDebug() << "tworze canvas";
	update();
}

void Canvas::paintEvent(QPaintEvent *paintEvent)
{
	qDebug() << "painting canvas";
	QPainter painter(this);
	painter.drawImage(paintEvent->rect(), *layers.back(), layers.back()->rect());
}

void Canvas::LoadImage(QString &fileName)
{
	//pixmap.load(fileName);
}

Canvas::~Canvas()
{
	for( auto layer : layers )
	{
		delete layer;
		layer = nullptr;
	}
}
