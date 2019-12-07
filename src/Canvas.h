//
// Created by waxta on 27.08.19.
//

#pragma once

#include <QGraphicsView>
#include "ImageLayer.h"

class Canvas : public QGraphicsView
{
Q_OBJECT

public:
	explicit Canvas(QWidget* parent);

	~Canvas() override;

private:
	QVector<ImageLayer*> layers;

	ImageLayer* activeLayer;
};


