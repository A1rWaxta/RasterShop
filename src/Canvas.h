//
// Created by waxta on 27.08.19.
//

#pragma once


#include <QtWidgets/QWidget>
#include <QtCore/QTimer>
#include "ImageLayer.h"

class Canvas : public QWidget
{
public:
	Canvas(QWidget *parent, const QPoint &position, const QSize &size, std::vector<ImageLayer> &layers,
	       unsigned int frameTime = 0);

	void LoadImage(QString & fileName);

private:
	void paintEvent(QPaintEvent * paintEvent) override;

	QTimer timer;

	QPixmap & pixmap;

	std::vector<ImageLayer> & layers;
};


