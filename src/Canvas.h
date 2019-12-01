//
// Created by waxta on 27.08.19.
//

#pragma once

#include <QtWidgets/QWidget>
#include <QtCore/QTimer>
#include "ImageLayer.h"

class Canvas : public QWidget
{
	Q_OBJECT

	friend class MainWindow;

public:
	Canvas(QWidget *parent);

	void LoadImage(QString & fileName);

	~Canvas();

private:
	void CreateCanvas(QSize size, QColor backgroundColor);

	void paintEvent(QPaintEvent * paintEvent) override;

	std::vector<ImageLayer*> layers;

	QTimer timer;

	QRect canvasSpace;

	QSize canvasSize;
};


