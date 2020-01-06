//
// Created by waxta on 03.12.19.
//

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "GraphicsScene.h"

GraphicsScene::GraphicsScene(qreal width, qreal height, QObject* parent) : QGraphicsScene(parent),
                                                                           leftMousePressed(false),
                                                                           activeLayer(nullptr),
                                                                           activeTool(ActiveTool::None)
{
	canvas = new Canvas(0, 0, width, height);
	addItem(canvas);
	connect(this, &QGraphicsScene::sceneRectChanged, this, &GraphicsScene::AdjustCanvasToSceneRect);

	selectionRectangle = new QGraphicsRectItem(0, 0, 0, 0);
	selectionRectangle->setPen(QPen(Qt::black, 1, Qt::DashDotDotLine));
	addItem(selectionRectangle);
}

void GraphicsScene::SetActiveLayer(ImageLayer* layer)
{
	activeLayer = layer;
	selectionRectangle->setRect(activeLayer->boundingRect());
	selectionRectangle->setPos(activeLayer->pos());
}

void GraphicsScene::AddItemOnActiveLayer(QGraphicsItem* item)
{
	item->setParentItem(activeLayer);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	QGraphicsScene::mouseMoveEvent(mouseEvent);

	qreal xPos;
	qreal yPos;

	if( leftMousePressed )
	{
		mousePointerDistance += std::abs(( mouseEvent->pos().x() - mouseEvent->lastPos().x() ) +
		                                 ( mouseEvent->pos().y() - mouseEvent->lastPos().y() ));
		switch( activeTool )
		{
			case ActiveTool::Move:
			{
				xPos = mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x();
				yPos = mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y();
				activeLayer->moveBy(xPos, yPos);
				selectionRectangle->moveBy(xPos, yPos);
				break;
			}
			case ActiveTool::Pen:
			{
				if( activeLayer->contains(mouseEvent->pos()) )
				{
					qDebug() << "rysowańsko";
					auto line = new QGraphicsLineItem(QLineF(mouseEvent->pos(), mouseEvent->lastPos()));
					line->setPen(QPen(QColor(123, 13, 123), 2));
					line->setParentItem(activeLayer);
				}
				break;
			}
			case ActiveTool::RectangleShape:
			{
				break;
			}
		}
	}
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	QGraphicsScene::mousePressEvent(mouseEvent);

	if( mouseEvent->button() == Qt::LeftButton and activeLayer != nullptr and
	    activeLayer->sceneBoundingRect().contains(mouseEvent->scenePos()) )
	{
		leftMousePressed = true;
	}
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	QGraphicsScene::mouseReleaseEvent(mouseEvent);

	mousePointerDistance = 0;

	if( mouseEvent->button() == Qt::LeftButton )
	{
		leftMousePressed = false;
	}
}

void GraphicsScene::ChangeActiveTool(ActiveTool tool)
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
	QPixmap pixmap = QPixmap::fromImage(QGuiApplication::clipboard()->image());
	if( pixmap.size().width() > 0 and pixmap.size().height() > 0 )
	{
		auto graphicsPixmap = new QGraphicsPixmapItem(pixmap, activeLayer);
		qreal xPos = canvas->rect().center().x() - ( pixmap.width() / 2 );
		qreal yPos = canvas->rect().center().y() - ( pixmap.height() / 2 );
		graphicsPixmap->setPos(xPos, yPos);
	}
}

void GraphicsScene::AdjustCanvasToSceneRect()
{
	setSceneRect(canvas->sceneBoundingRect());
}