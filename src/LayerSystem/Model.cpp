//
// Created by waxta on 1/1/20.
//

#include "Model.h"

using LayerSystem::Model;

Model::Model()
{
}

void Model::CreateLayer()
{
	static int numberOfLayers = 0;
	QString layerIdentifier = "layer_" + QString::number(numberOfLayers);
	auto layer = new ImageLayer(layerIdentifier);
	layer->setZValue(layerStack.size());
	layerStack.push_back(layer);
	++numberOfLayers;
	activeLayer = layer;

	//todo: add layer to graphics scene

	view->Update();
}

void Model::DeleteActiveLayer()
{
	auto iterator = std::find(layerStack.begin(), layerStack.end(), activeLayer);
	int index = std::distance(layerStack.begin(), iterator);
	delete layerStack[index];
	layerStack.erase(iterator);
	for( int i = index; i < layerStack.size(); ++i )
	{
		layerStack[i]->setZValue(i);
	}

	view->Update();
}

void Model::MoveActiveLayer(LayerMoveDirection moveDirection)
{
	auto iterator = std::find(layerStack.begin(), layerStack.end(), activeLayer);
	switch( moveDirection )
	{
		case LayerMoveDirection::Up:
		{
			if( iterator != layerStack.begin() )
			{
				std::iter_swap(iterator, iterator - 1);
			}
		}
		case LayerMoveDirection::Down:
		{
			if( iterator != layerStack.end() )
			{
				std::iter_swap(iterator, iterator + 1);
			}
		}
	}
	view->Update();
}

void Model::AttachView(View* view)
{
	this->view = view;
	this->view->ObserveLayerModel(this);
	view->Update();
}

std::vector<ImageLayer*> Model::GetLayers()
{
	return layerStack;
}
