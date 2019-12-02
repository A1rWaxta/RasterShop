//
// Created by waxta on 27.08.19.
//

#include "Canvas.h"
#include <QPainter>
#include <QDebug>
#include <QPaintEvent>

Canvas::Canvas(QWidget *parent) : QWidget(parent), canvasSize(0, 0)
{
}

void Canvas::paintEvent(QPaintEvent *paintEvent)
{
 	QPainter painter(this);
 	for( auto layer : layers )
    {
	    painter.drawImage(renderArea, *layer, layer->rect());
    }
}

void Canvas::LoadImage(QString &fileName)
{
}

Canvas::~Canvas()
{
	for( auto layer : layers )
	{
		delete layer;
		layer = nullptr;
	}
}

void Canvas::CreateCanvas(QSize size, QColor backgroundColor)
{
	const int centerY = width() / 2 - size.width() / 2;
	const int centerX = height() / 2 - size.height() / 2;
	canvasSize = size;
	renderArea = QRect(QPoint(centerY, centerX), size);
	QImage tmpImage(renderArea.size(), QImage::Format_ARGB32);
	tmpImage.fill(backgroundColor);
	layers.push_back(new ImageLayer(tmpImage));
	update();
}

void Canvas::HorizontalSliderMoved(int value)
{
}

void Canvas::VerticalSliderMoved(int value)
{
}