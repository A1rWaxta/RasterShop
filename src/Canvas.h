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
	Canvas();

	void LoadImage(QString & fileName);

	~Canvas();

public slots:
	void HorizontalSliderMoved(int value);

	void VerticalSliderMoved(int value);

private:
	void SetRenderAreaSize(QSize size);

	void paintEvent(QPaintEvent * paintEvent) override;

	void CreateLayer(QColor backgroundColor = Qt::transparent);

	std::vector<ImageLayer*> layers;

	QRect renderArea;
};


