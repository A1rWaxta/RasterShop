//
// Created by waxta on 03.12.19.
//

#pragma once

#include <QtWidgets>
#include "Globals.h"
#include "ImageLayer.h"
#include "Canvas.h"
#include "RectangleSelectionTool.h"
#include "ScaleTool.h"
#include "RotationTool.h"
#include "TextTool.h"
#include "PolygonTool.h"

class GraphicsScene : public QGraphicsScene
{
Q_OBJECT

	friend class MainWindow;

public:
	GraphicsScene(qreal width, qreal height, QColor& color, QFont& font, int& fontSize, QObject* parent);

public slots:
	void ChangeActiveTool(ActiveTool tool);
	void Paste();
	void CancelSelection();
	void ToggleLayerSelectionVisibility();

private slots:
	void AdjustCanvasToSceneRect();

private:
	void AddItemOnActiveLayer(QGraphicsItem* item);
	void AddLayer(ImageLayer* layer);
	void ChangeActiveLayer(ImageLayer* layer);
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void HideTools();
	void ShowTools();
	bool leftMousePressed;
	ImageLayer* activeLayer;
	Canvas* canvas;
	qreal mousePointerDistance;
	ActiveTool activeTool;
	QColor& toolColor;
	QFont& font;
	int& textSize;

	QGraphicsRectItem layerSelection;
	RectangleSelectionTool rectangleSelectionTool;
	ScaleTool scaleTool;
	RotationTool rotationTool;
	PolygonTool polygonTool;
};
