//
// Created by waxta on 03.12.19.
//

#pragma once

#include <QtWidgets>
#include "Globals.h"
#include "ImageLayer.h"

class GraphicsScene : public QGraphicsScene
{
Q_OBJECT

	friend class MainWindow;

public:
	GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject* parent = nullptr);

	explicit GraphicsScene(QObject* parent);

public slots:
	void ToolSelected(ActiveTool tool);

private:
	void AddItemOnActiveLayer(QGraphicsItem* item);

	void AddLayer(ImageLayer* layer);

	void CreateBackground(int width, int height);

	void SetActiveLayer(ImageLayer* layer);

	void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

	void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

	void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

	void keyPressEvent(QKeyEvent* event) override;

	bool leftMousePressed;

	ImageLayer* activeLayer;

	QGraphicsRectItem* workSpace;

	ActiveTool activeTool;
};
