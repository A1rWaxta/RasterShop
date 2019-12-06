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

	void LoadImage(QString& fileName);

	QString& CreateLayer();

	void AddItem(QGraphicsItem* item);

private:
	void SetRenderAreaSize(QSize size);

	QVector<ImageLayer*> layers;

	ImageLayer* activeLayer;

	QRect renderArea;
};


