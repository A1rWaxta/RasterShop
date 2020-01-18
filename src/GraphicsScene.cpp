//
// Created by waxta on 03.12.19.
//

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "GraphicsScene.h"
#include "TextTool.h"

GraphicsScene::GraphicsScene(qreal width, qreal height, QColor& color, QFont& font, int& fontSize, QObject* parent)
		: QGraphicsScene(parent),
		  leftMousePressed(false),
		  activeLayer(nullptr),
		  toolColor(color),
		  layerSelection(0, 0, 0, 0),
		  font(font),
		  textSize(fontSize),
		  activeTool(ActiveTool::None)
{
	canvas = new Canvas(0, 0, width, height);
	addItem(canvas);
	connect(this, &QGraphicsScene::sceneRectChanged, this, &GraphicsScene::AdjustCanvasToSceneRect);

	layerSelection.setPen(QPen(Qt::black, 1, Qt::DashDotDotLine));

	addItem(&layerSelection);
	addItem(&rectangleSelectionTool);
	addItem(&scaleTool);
	addItem(&rotationTool);
	addItem(&polygonTool);
}

void GraphicsScene::ChangeActiveLayer(ImageLayer* layer)
{
	activeLayer = layer;
	if( activeLayer != nullptr )
	{
		layerSelection.show();
		layerSelection.setRect(layerSelection.mapRectFromScene(activeLayer->mappedToSceneBoundingRect()));

		switch( activeTool )
		{
			case ActiveTool::Scale:
			{
				scaleTool.SetLayer(activeLayer);
				break;
			}
			case ActiveTool::Rotation:
			{
				rotationTool.SetLayer(activeLayer);
				break;
			}
			case ActiveTool::Text:
			{

				break;
			}
			default:
			{
				break;
			}
		}
	}
	else
	{
		scaleTool.hide();
		layerSelection.hide();
	}
}

void GraphicsScene::AddItemOnActiveLayer(QGraphicsItem* item)
{
	item->setParentItem(activeLayer);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsScene::mousePressEvent(event);
	if( event->button() == Qt::LeftButton and activeLayer != nullptr )
	{
		switch( activeTool )
		{
			case ActiveTool::Pen:
			{
				if( activeLayer->mappedToSceneBoundingRect().contains(event->scenePos()) )
				{
					leftMousePressed = true;
				}
				break;
			}
			case ActiveTool::Selection:
			{
				leftMousePressed = true;
				rectangleSelectionTool.Start(event->scenePos());
				break;
			}
			case ActiveTool::Paint:
			{
				QPolygonF layerPolygon(activeLayer->mapToScene(activeLayer->rect()));
				QPolygonF selectionPolygon;
				QPolygonF paintPolygon;
				if( rectangleSelectionTool.GetSelectedRegion().contains(event->scenePos()) )
				{
					selectionPolygon = QPolygonF(rectangleSelectionTool.boundingRect());
					paintPolygon = selectionPolygon.intersected(layerPolygon);

				}
				if( polygonTool.GetPolygon().containsPoint(event->scenePos(), Qt::WindingFill) )
				{
					selectionPolygon = polygonTool.GetPolygon();
					paintPolygon = selectionPolygon.intersected(layerPolygon);
				}
				auto graphicsPolygon = new QGraphicsPolygonItem(activeLayer->mapFromScene(paintPolygon));
				graphicsPolygon->setPen(Qt::NoPen);
				graphicsPolygon->setBrush(toolColor);
				AddItemOnActiveLayer(graphicsPolygon);
				break;
			}
			case ActiveTool::Move:
			{
				if( activeLayer->mappedToSceneBoundingRect().contains(event->scenePos()) )
				{
					leftMousePressed = true;
				}
				break;
			}
			case ActiveTool::Scale:
			{
				if( scaleTool.IsPointRectangleSelected(event->scenePos()) )
				{
					leftMousePressed = true;
					scaleTool.Start();
				}
				break;
			}
			case ActiveTool::Text:
			{
				if( activeLayer->mappedToSceneBoundingRect().contains(event->scenePos()) )
				{
					auto text = new TextTool();
					text->setFont(QFont(font.family(), textSize));
					text->setDefaultTextColor(toolColor);
					text->SetLayer(activeLayer);
					AddItemOnActiveLayer(text);
					text->Start(event->pos());
					setFocusItem(text);
				}
				break;
			}
			case ActiveTool::Polygon:
			{
				polygonTool.AddPoint(event->scenePos());
			}
		}
	}
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsScene::mouseMoveEvent(event);

	qreal xPos;
	qreal yPos;

	if( leftMousePressed )
	{
		mousePointerDistance += std::abs(( event->pos().x() - event->lastPos().x() ) +
		                                 ( event->pos().y() - event->lastPos().y() ));
		switch( activeTool )
		{
			case ActiveTool::Move:
			{
				xPos = event->scenePos().x() - event->lastScenePos().x();
				yPos = event->scenePos().y() - event->lastScenePos().y();
				activeLayer->moveBy(xPos, yPos);
				layerSelection.moveBy(xPos, yPos);
				break;
			}
			case ActiveTool::Pen:
			{
				if( activeLayer->mappedToSceneBoundingRect().contains(event->scenePos()) )
				{
					auto line = new QGraphicsLineItem(QLineF(activeLayer->mapFromScene(event->scenePos()),
					                                         activeLayer->mapFromScene(event->lastScenePos())));
					line->setPen(QPen(toolColor, 10));
					line->setParentItem(activeLayer);
				}
				break;
			}
			case ActiveTool::Selection:
			{
				rectangleSelectionTool.Update(event->scenePos());
				break;
			}
			case ActiveTool::Scale:
			{
				scaleTool.Update(event->scenePos());
				layerSelection.setRect(layerSelection.mapRectFromScene(activeLayer->mappedToSceneBoundingRect()));
				break;
			}
			case ActiveTool::Rotation:
			{
				layerSelection.setRect(activeLayer->mappedToSceneBoundingRect());
				break;
			}
		}
	}
	layerSelection.setRect(layerSelection.mapRectFromScene(activeLayer->mappedToSceneBoundingRect()));
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsScene::mouseReleaseEvent(event);

	mousePointerDistance = 0;

	if( event->button() == Qt::LeftButton )
	{
		leftMousePressed = false;

		if( activeTool == ActiveTool::Rotation )
		{
			rotationTool.Stop();
		}
	}
}

void GraphicsScene::ChangeActiveTool(ActiveTool tool)
{
	scaleTool.hide();
	rotationTool.hide();

	if( activeLayer != nullptr )
	{
		activeTool = tool;
	}
	else
	{
		return;
	}

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
		{
			scaleTool.show();
			scaleTool.SetLayer(activeLayer);
			break;
		}
		case ActiveTool::Rotation:
		{
			rotationTool.show();
			rotationTool.SetLayer(activeLayer);
			break;
		}
		case ActiveTool::Text:
		{
		}
		case ActiveTool::Polygon:
		{
			polygonTool.Clear();
		}
		default:
			break;
	}
}

void GraphicsScene::keyPressEvent(QKeyEvent* event)
{
	QGraphicsScene::keyPressEvent(event);

	if( activeTool == ActiveTool::Polygon )
	{
		if( event->key() == Qt::Key_Return )
		{
			if( polygonTool.NumberOfPoints() > 2 )
			{
				polygonTool.Close();
			}
		}
	}
}

void GraphicsScene::AddLayer(ImageLayer* layer)
{
	layer->setParentItem(canvas);
	layer->setTransformOriginPoint(layer->mappedToSceneBoundingRect().width() / 2,
	                               layer->mappedToSceneBoundingRect().height() / 2);
}

void GraphicsScene::Paste()
{
	QPixmap pixmap = QPixmap::fromImage(QGuiApplication::clipboard()->image());
	if( pixmap.size().width() > 0 and pixmap.size().height() > 0 )
	{
		auto graphicsPixmap = new QGraphicsPixmapItem;
		graphicsPixmap->setPixmap(pixmap);
		graphicsPixmap->setParentItem(activeLayer);
		qreal xPos = canvas->rect().center().x() - ( pixmap.width() / 2 );
		qreal yPos = canvas->rect().center().y() - ( pixmap.height() / 2 );
	}
}

void GraphicsScene::AdjustCanvasToSceneRect()
{
	setSceneRect(canvas->sceneBoundingRect());
}

void GraphicsScene::CancelSelection()
{
	rectangleSelectionTool.setRect(QRectF(0, 0, 0, 0));
	polygonTool.Clear();
}

void GraphicsScene::ToggleLayerSelectionVisibility()
{
	if( layerSelection.isVisible() )
	{
		layerSelection.hide();
	}
	else
	{
		layerSelection.show();
	}
}

void GraphicsScene::HideTools()
{
	if( activeTool == ActiveTool::Rotation )
	{
		rotationTool.hide();
	}
	else if( activeTool == ActiveTool::Scale )
	{
		scaleTool.hide();
	}
	else if( activeTool == ActiveTool::Selection )
	{
		rectangleSelectionTool.hide();
	}
	layerSelection.hide();
}

void GraphicsScene::ShowTools()
{
	if( activeTool == ActiveTool::Rotation )
	{
		rotationTool.show();
	}
	else if( activeTool == ActiveTool::Scale )
	{
		scaleTool.show();
	}
	else if( activeTool == ActiveTool::Selection )
	{
		rectangleSelectionTool.show();
	}
	layerSelection.show();
}