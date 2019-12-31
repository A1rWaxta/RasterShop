#include <QtCore/QSignalMapper>
#include "LayersView.h"
#include "ui_LayersView.h"
#include <QDebug>

LayersView::LayersView(QWidget* parent) :
		QWidget(parent),
		ui(new Ui::LayersView)
{
	ui->setupUi(this);
	ui->layersLayout->setAlignment(Qt::AlignTop);

	connect(ui->addLayer, &QPushButton::released, this, &LayersView::CreateLayer);
	connect(ui->deleteLayer, &QPushButton::released, this, &LayersView::DeleteLayer);
	connect(ui->moveLayerUp, &QPushButton::clicked, this, [this]
	{ MoveLayer(LayerMoveDirection::Up); });
	connect(ui->moveLayerDown, &QPushButton::clicked, this, [this]
	{ MoveLayer(LayerMoveDirection::Down); });

	DisableButtons();
}

LayersView::~LayersView()
{
	delete ui;
}

void LayersView::CreateLayer()
{
//	auto newLayer = new ImageLayer();
//	newLayer->setZValue(layers.size()); //places new layer on top of image
//	graphicsScene->AddLayer(newLayer);
//
//	QString layerName = "layer_" + QString::number(layersAddedCount);
//	auto layerPreview = new LayerPreview(newLayer, layerName, ui->scrollAreaWidgetContents);
//	ui->layerPreviewLayout->addWidget(layerPreview);
//	layers.push_back(layerPreview);
//	++layersAddedCount;
//
//	connect(layerPreview, &LayerPreview::Selected, this, &MainWindow::ActiveLayerChanged);
//
//	ActiveLayerChanged(layerPreview);
}

void LayersView::DeleteLayer()
{
//	auto decrementLayerZValue = [](LayerPreview* preview)
//	{
//		int zValue = preview->GetLayer()->zValue();
//		preview->GetLayer()->setZValue(zValue - 1);
//	};
//
//	auto iterator = std::find(layers.begin(), layers.end(), activeLayer);
//	int index = std::distance(layers.begin(), iterator);
//	QLayoutItem* item = ui->layerPreviewLayout->takeAt(index);
//	delete item->widget();
//	delete item;
//	layers.erase(iterator);
//	std::for_each(iterator, layers.end(), decrementLayerZValue);
//
//	if( not layers.empty() )
//	{
//		activeLayer = layers[index != 0 ? index - 1 : index];
//		graphicsScene->SetActiveLayer(activeLayer->GetLayer());
//		activeLayer->Select();
//	}
//	else
//	{
//		activeLayer = nullptr;
//		graphicsScene->SetActiveLayer(nullptr);
//	}
}

void LayersView::MoveLayer(LayerMoveDirection direction)
{
//	auto layersVectorIterator = std::find(layers.begin(), layers.end(), activeLayer);
//	int index = std::distance(layers.begin(), layersVectorIterator);
//	LayerPreview* tmpWidget;
//	int zValue;
//
//	switch( direction )
//	{
//		case LayerMoveDirection::Up:
//			if( index == 0 )
//			{
//				return;
//			}
//			tmpWidget = dynamic_cast<LayerPreview*>(ui->layerPreviewLayout->itemAt(index - 1)->widget());
//			zValue = tmpWidget->GetLayer()->zValue();
//			tmpWidget->GetLayer()->setZValue(activeLayer->GetLayer()->zValue());
//			activeLayer->GetLayer()->setZValue(zValue);
//			ui->layerPreviewLayout->removeWidget(tmpWidget);
//			ui->layerPreviewLayout->removeWidget(activeLayer);
//			ui->layerPreviewLayout->insertWidget(index - 1, activeLayer);
//			ui->layerPreviewLayout->insertWidget(index, tmpWidget);
//			std::iter_swap(layersVectorIterator, layersVectorIterator - 1);
//			break;
//
//		case LayerMoveDirection::Down:
//			if( index == layers.size() - 1 )
//			{
//				return;
//			}
//			tmpWidget = dynamic_cast<LayerPreview*>(ui->layerPreviewLayout->itemAt(index + 1)->widget());
//			zValue = tmpWidget->GetLayer()->zValue();
//			tmpWidget->GetLayer()->setZValue(activeLayer->GetLayer()->zValue());
//			activeLayer->GetLayer()->setZValue(zValue);
//			ui->layerPreviewLayout->removeWidget(tmpWidget);
//			ui->layerPreviewLayout->removeWidget(activeLayer);
//			ui->layerPreviewLayout->insertWidget(index, tmpWidget);
//			ui->layerPreviewLayout->insertWidget(index + 1, activeLayer);
//			std::iter_swap(layersVectorIterator, layersVectorIterator + 1);
//			break;
//	}
}

void LayersView::EnableButtons()
{
	ui->addLayer->setEnabled(true);
	ui->deleteLayer->setEnabled(true);
	ui->moveLayerDown->setEnabled(true);
	ui->moveLayerUp->setEnabled(true);
}
void LayersView::DisableButtons()
{
	ui->addLayer->setEnabled(false);
	ui->deleteLayer->setEnabled(false);
	ui->moveLayerDown->setEnabled(false);
	ui->moveLayerUp->setEnabled(false);
}
