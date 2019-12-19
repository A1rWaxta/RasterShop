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
	if(event->key() == Qt::Key_F4)
	{
		activeLayer->moveBy(-10, 0);
	}
}

void GraphicsScene::AddLayer(ImageLayer* layer)
{
	layer->setParentItem(workSpace);
}

void GraphicsScene::CreateBackground(int width, int height)
{
	workSpace = new QGraphicsRectItem(0, 0, width - 1, height - 1);
	workSpace->setPen(Qt::NoPen);
	workSpace->setBrush(QBrush(Qt::gray));
	workSpace->setFlag(QGraphicsItem::ItemClipsChildrenToShape);
	addItem(workSpace);
}