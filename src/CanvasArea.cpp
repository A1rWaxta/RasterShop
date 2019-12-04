//
// Created by waxta on 03.12.19.
//

#include "CanvasArea.h"
#include <QKeyEvent>
#include <QGuiApplication>

#ifdef DEBUG

#include <QDebug>

#endif

CanvasArea::CanvasArea(QWidget* parent) : QScrollArea(parent)
{
	installEventFilter(this);
}

void CanvasArea::wheelEvent(QWheelEvent* event)
{
	if( QGuiApplication::queryKeyboardModifiers() == Qt::AltModifier)
	{

	}
	QScrollArea::wheelEvent(event);
}