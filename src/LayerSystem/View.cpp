//
// Created by waxta on 1/1/20.
//

#include <LayerPreview.h>
#include "View.h"

using LayerSystem::View;

View::View()
{
	auto scrollAreaWidget = new QWidget();
	setWidget(scrollAreaWidget); //becomes a child
	layout = new QVBoxLayout();
	layout->setAlignment(Qt::AlignTop);
	scrollAreaWidget->setLayout(layout);
}

void View::Update()
{
	QLayoutItem* item;
	LayerPreview* layerPreview;
	int currentNumberOfItems = layout->count();
	auto layers = model->GetLayers();

	if( currentNumberOfItems != layers.size() )
	{
		if( currentNumberOfItems < layers.size() )
		{
			for( int i = 0; i < ( layers.size() - currentNumberOfItems ); ++i )
			{
				layerPreview = new LayerPreview();
				layout->addWidget(layerPreview);
			}
		}
		else
		{
			for( int i = 0; i < ( currentNumberOfItems - layers.size() ); ++i )
			{
				item = layout->takeAt(0);
				delete item->widget();
				delete item;
			}
		}
	}
	for( int i = 0; i < layers.size(); ++i )
	{
		layerPreview = dynamic_cast<LayerPreview*>(layout->itemAt(i)->widget());
		layerPreview->SetLayerName(layers[i]->GetLayerIdentifier());
	}
}

void View::ObserveLayerModel(LayerSystem::Model* model)
{
	this->model = model;
}
