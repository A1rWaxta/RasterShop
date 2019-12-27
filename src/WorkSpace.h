//
// Created by waxta on 27.08.19.
//

#pragma once

#include <QGraphicsView>
#include "ImageLayer.h"
#include "Canvas.h"
#include <QShortcut>

class Canvas;
class WorkSpace : public QGraphicsView
{
Q_OBJECT

public:
	explicit WorkSpace(QWidget* parent);
	~WorkSpace() override;

private:
	void wheelEvent(QWheelEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	QVector<ImageLayer*> layers;
	ImageLayer* activeLayer;
	QShortcut* ctrlC;
	QShortcut* ctrlV;
};