//
// Created by waxta on 03.12.19.
//

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "GraphicsScene.h"

GraphicsScene::GraphicsScene(qreal width, qreal height, QColor& color, QObject* parent) : QGraphicsScene(parent),
                                                                                          leftMousePressed(false),
                                                                                          activeLayer(nullptr),
                                                                                          toolColor(color),
                                                                                          activeTool(ActiveTool::None)
{
	canvas = new Canvas(0, 0, width, height);
	addItem(canvas);
	connect(this, &QGraphicsScene::sceneRectChanged, this, &GraphicsScene::AdjustCanvasToSceneRect);

	layerSelection = new QGraphicsRectItem(0, 0, 0, 0);
	layerSelection->setPen(QPen(Qt::black, 1, Qt::DashDotDotLine));
	addItem(layerSelection);

	addItem(&selectionTool);
	addItem(&scaleTool);
}

void GraphicsScene::SetActiveLayer(ImageLayer* layer)
{
	activeLayer = layer;
	if( activeLayer != nullptr )
	{
		layerSelection->show();
		layerSelection->setRect(activeLayer->boundingRect());
		layerSelection->setPos(activeLayer->pos());
		setFocusItem(activeLayer);

		if( activeTool == ActiveTool::Scale )
		{
			scaleTool.SetLayer(activeLayer);
		}
	}
	else
	{
		scaleTool.hide();
		layerSelection->hide();
	}
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
				break;
			}
			case ActiveTool::Pen:
			{
				if( activeLayer->contains(mouseEvent->pos()) )
				{
					auto line = new QGraphicsLineItem(QLineF(mouseEvent->pos(), mouseEvent->lastPos()));
					line->setPen(QPen(toolColor, 10));
					line->setParentItem(activeLayer);
				}
				break;
			}
			case ActiveTool::Selection:
			{
				selectionTool.Update(mouseEvent->scenePos());
				break;
			}
			case ActiveTool::Scale:
			{
				scaleTool.Update(mouseEvent->scenePos());
				break;
			}
		}
		layerSelection->moveBy(xPos, yPos);
	}
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	QGraphicsScene::mousePressEvent(mouseEvent);

	if( mouseEvent->button() == Qt::LeftButton and activeLayer != nullptr )
	{
		switch( activeTool )
		{
			case ActiveTool::Pen:
			{
				if( activeLayer->boundingRect().contains(mouseEvent->scenePos()) )
				{
					leftMousePressed = true;
				}
				break;
			}
			case ActiveTool::Selection:
			{
				leftMousePressed = true;
				selectionTool.Start(mouseEvent->scenePos());
				break;
			}
			case ActiveTool::Paint:
			{
				if( selectionTool.GetSelectedRegion().contains(mouseEvent->scenePos()) )
				{
					auto selectionAreaRectangle = new QGraphicsRectItem();
					selectionAreaRectangle->setRect(
							activeLayer->mapRectFromScene(
									activeLayer->boundingRect().intersected(selectionTool.GetSelectedRegion())));
					selectionAreaRectangle->setPen(Qt::NoPen);
					selectionAreaRectangle->setBrush(toolColor);
					AddItemOnActiveLayer(selectionAreaRectangle);
				}
				break;
			}
			case ActiveTool::Move:
			{
				if( activeLayer->boundingRect().contains(mouseEvent->scenePos()) )
				{
					leftMousePressed = true;
				}
				break;
			}
			case ActiveTool::Scale:
			{
				if( scaleTool.IsPointRectangleSelected(mouseEvent->scenePos()) )
				{
					leftMousePressed = true;
					scaleTool.Start();
				}
			}
		}
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

	scaleTool.hide();

	switch( tool )
	{
		case ActiveTool::None:
			break;

		case ActiveTool::Move:
			break;

		case ActiveTool::Pen:
			break;

		case ActiveTool::Paint:
			break;

		case ActiveTool::Scale:
			scaleTool.show();
			scaleTool.SetLayer(activeLayer);
			break;

		default:
			break;
	}
}

void GraphicsScene::keyPressEvent(QKeyEvent* event)
{
	if( event->key() == Qt::UpArrow )
	{
		if( activeTool == ActiveTool::Scale )
		{
			activeLayer->setScale(activeLayer->scale() + 0.1);
			activeLayer->setTransformOriginPoint(activeLayer->boundingRect().width() / 2,
			                                     activeLayer->boundingRect().height() / 2);
			layerSelection->setRect(activeLayer->boundingRect());
//			selectionRectangle->setPos()
		}
	}
}

void GraphicsScene::AddLayer(ImageLayer* layer)
{
	layer->setParentItem(canvas);
//	layer->setTransformOriginPoint(layer->boundingRect().width() / 2,
//	                               layer->boundingRect().height() / 2);
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

void GraphicsScene::CancelSelection()
{
	selectionTool.setRect(QRectF(0, 0, 0, 0));
}

void GraphicsScene::ToggleLayerSelectionVisibility()
{
	if( layerSelection->isVisible() )
	{
		layerSelection->hide();
	}
	else
	{
		layerSelection->show();
	}
}
