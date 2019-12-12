//
// Created by waxta on 03.12.19.
//

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "GraphicsScene.h"

GraphicsScene::GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject* parent) :
		QGraphicsScene(x, y, width, height, parent),
		activeLayer(nullptr),
		activeTool(ActiveTool::None)
{
	setBackgroundBrush(QBrush(QColor(127, 127, 127)));
	QPainter painter;
}

GraphicsScene::GraphicsScene(QObject* parent) : QGraphicsScene(parent), activeLayer(nullptr)
{

}

void GraphicsScene::SetActiveLayer(ImageLayer* layer)
{
	activeLayer = layer;
}

void GraphicsScene::AddItemOnActiveLayer(QGraphicsItem* item)
{
	item->setParentItem(activeLayer);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	int xPos;
	int yPos;
	if( leftMousePressed )
	{
		switch( activeTool )
		{
			case ActiveTool::Move:
//				xPos = event->lastScenePos().x() - event->scenePos().x();
//				yPos = event->lastScenePos().y() - event->scenePos().y();
				activeLayer->setPos(event->scenePos());
				break;

			default:
				break;
		}
	}
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if( mouseEvent->button() == Qt::LeftButton
	    and
	    sceneRect().contains(mouseEvent->scenePos())
	    )
	{
		leftMousePressed = true;
		qDebug() << mouseEvent->scenePos();
	}
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if( mouseEvent->button() != Qt::LeftButton )
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
	if(event->key() == Qt::Key_F4)
	{
		activeLayer->moveBy(-10, 0);
	}
}