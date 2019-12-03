//
// Created by waxta on 03.12.19.
//

#pragma once


#include <QtWidgets/QScrollArea>

class CanvasArea : public QScrollArea
{
public:
	CanvasArea(QWidget * parent);

private:
	void wheelEvent(QWheelEvent * event) override;
};


