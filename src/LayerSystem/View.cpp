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
	layout = new QVBoxLayout(widget());
}

void View::Update()
{
	int count = layout->count();
	auto layers = model->GetLayers();
	for(int i = 0; i < layers.size(); ++i)
	{
		auto layerPreview = dynamic_cast<LayerPreview*>(layout->itemAt(i)->widget());
		layerPreview->SetText(layers[i].GetLayerIdentifier());
	}
}

void LayerSystem::View::ObserveLayerModel(LayerSystem::Model* model)
{
	this->model = model;
}
