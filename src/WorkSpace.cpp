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
	setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	setAttribute(Qt::WA_InputMethodEnabled);
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
	QGraphicsView::keyPressEvent(event);
}

void WorkSpace::inputMethodEvent(QInputMethodEvent* event)
{
	QGraphicsView::inputMethodEvent(event);
}

QVariant WorkSpace::inputMethodQuery(Qt::InputMethodQuery query) const
{
	return QGraphicsView::inputMethodQuery(query);
}