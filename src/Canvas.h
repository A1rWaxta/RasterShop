//
// Created by waxta on 27.08.19.
//

#pragma once

#include <QGraphicsView>
#include "ImageLayer.h"

class Canvas : public QGraphicsView
{
Q_OBJECT

	friend class MainWindow;

public:
	Canvas(QWidget* parent);

	void LoadImage(QString& fileName);

	~Canvas();

public slots:

	void HorizontalSliderMoved(int value);

	void VerticalSliderMoved(int value);

private:
	void SetRenderAreaSize(QSize size);

	void CreateLayer();

	QVector<ImageLayer> layers;

	QRect renderArea;
};


