//
// Created by waxta on 03.12.19.
//

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "GraphicsScene.h"

GraphicsScene::GraphicsScene(qreal width, qreal height, QObject* parent) : QGraphicsScene(parent), activeLayer(nullptr),
                                                                           canvas(nullptr),
                                                                           leftMousePressed(false),
                                                                           activeTool(ActiveTool::None)
{
	auto canvas = new Canvas(0, 0, width, height);
	this->canvas = canvas;
	addItem(canvas);
	connect(this, &QGraphicsScene::sceneRectChanged, this, &GraphicsScene::AdjustCanvasToSceneRect);
}

void GraphicsScene::SetActiveLayer(ImageLayer* layer)
{
	activeLayer = layer;
}

void GraphicsScene::AddItemOnActiveLayer(QGraphicsItem* item)
{
	item->setParentItem(activeLayer);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	qreal xPos;
	qreal yPos;
	if( leftMousePressed )
	{
		switch( activeTool )
		{
			case ActiveTool::Move:
				xPos = mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x();
				yPos = mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y();
				activeLayer->moveBy(xPos, yPos);
				break;

			case ActiveTool::Pen:
				auto ellipse = new QGraphicsEllipseItem(mouseEvent->scenePos().x(), mouseEvent->scenePos().y(), 10, 10);
				ellipse->setBrush(QColor(123, 123, 123));
				ellipse->setPen(Qt::NoPen);
				ellipse->setParentItem(activeLayer);
				break;
		}
	}
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if( mouseEvent->button() == Qt::LeftButton )
	{
	}
	if( activeLayer->sceneBoundingRect().contains(mouseEvent->scenePos()))
	{
		activeLayer->setSelected(true);
		leftMousePressed = true;
	}
	else
	{

	}
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if( mouseEvent->button() == Qt::LeftButton )
	{
		leftMousePressed = false;
	}
}

void GraphicsScene::ToolSelected(ActiveTool tool)
{
	activeTool = tool;
	switch( tool )
	{
		case ActiveTool::None:
			break;

		case ActiveTool::Move:
			break;

		case ActiveTool::Pen:
			break;

		default:
			break;
	}
}

void GraphicsScene::keyPressEvent(QKeyEvent* event)
{
}

void GraphicsScene::AddLayer(ImageLayer* layer)
{
	layer->setParentItem(canvas);
}

void GraphicsScene::Paste()
{
	auto clipboard = QGuiApplication::clipboard();
	QImage image = clipboard->image();
	auto graphicsPixmap = new QGraphicsPixmapItem(QPixmap::fromImage(image));
	AddItemOnActiveLayer(graphicsPixmap);
}

void GraphicsScene::AdjustCanvasToSceneRect()
{
	setSceneRect(canvas->sceneBoundingRect());
}