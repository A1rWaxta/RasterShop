//
// Created by waxta on 03.12.19.
//

#pragma once

#include <QtWidgets>
#include "Globals.h"
#include "ImageLayer.h"
#include "Canvas.h"

class GraphicsScene : public QGraphicsScene
{
Q_OBJECT

	friend class MainWindow;

public:
	explicit GraphicsScene(QObject* parent);
	void SetCanvas(Canvas* canvas);

public slots:
	void ToolSelected(ActiveTool tool);

private:
	void AddItemOnActiveLayer(QGraphicsItem* item);
	void AddLayer(ImageLayer* layer);
	void SetActiveLayer(ImageLayer* layer);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
	void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
	void keyPressEvent(QKeyEvent* event) override;
	bool leftMousePressed;
	ImageLayer* activeLayer;
	Canvas* canvas;
	ActiveTool activeTool;
};
