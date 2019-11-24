//
// Created by waxta on 23.11.19.
//

#include "ToolBarButton.h"
#include <QDebug>

ToolBarButton::ToolBarButton(QWidget *parent) : QPushButton(parent)
{

}

void ToolBarButton::paintEvent(QPaintEvent *paintEvent)
{
	QPushButton::paintEvent(paintEvent);
}

void ToolBarButton::enterEvent(QEvent *event)
{

}

void ToolBarButton::SetToolTip(QString &toolTip)
{
	this->toolTip = toolTip;
}
