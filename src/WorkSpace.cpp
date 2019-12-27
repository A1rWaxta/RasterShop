//
// Created by waxta on 27.08.19.
//

#include "WorkSpace.h"
#include <QPaintEvent>
#include <QDebug>
#include <QtGui/QGuiApplication>

WorkSpace::WorkSpace(QWidget* parent)
{
	setTransformationAnchor(AnchorUnderMouse);
}

WorkSpace::~WorkSpace()
{
}

void WorkSpace::wheelEvent(QWheelEvent* event)
{
	if( QGuiApplication::keyboardModifiers() == Qt::KeyboardModifier::ControlModifier )
	{
		if( event->delta() > 0 )
		{
			scale(1.1, 1.1);
		}
		if( event->delta() < 0 )
		{
			scale(0.9, 0.9);
		}
	}
}

void WorkSpace::keyPressEvent(QKeyEvent* event)
{
	QTransform currentTranform = transform();
	QTransform newTranform = currentTranform;
	QPointF centerPoint = rect().center();
	if( event->key() == Qt::Key_Up )
	{
	}
	if( event->key() == Qt::Key_Down )
	{
	}
}