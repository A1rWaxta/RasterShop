//
// Created by waxta on 1/1/20.
//

#include "Controller.h"
#include "Globals.h"

using LayerSystem::Controller;

Controller::Controller(Model* model, View* view) : model(model), view(view)
{
	addLayer = new QPushButton(tr("Dodaj"));
	addLayer->setEnabled(true);

	deleteLayer = new QPushButton(tr("Usuń"));

	moveLayerUp = new QPushButton(tr("Góra"));

	moveLayerDown = new QPushButton(tr("Dół"));

	addWidget(addLayer);
	addWidget(deleteLayer);
	addWidget(moveLayerUp);
	addWidget(moveLayerDown);

	connect(addLayer, &QPushButton::released, this, &Controller::AddLayerButtonClicked);
	connect(deleteLayer, &QPushButton::released, this, &Controller::DeleteLayerButtonClicked);
	connect(moveLayerDown, &QPushButton::released, this, &Controller::MoveLayerDownButtonClicked);
	connect(moveLayerUp, &QPushButton::released, this, &Controller::MoveLayerUpButtonClicked);
}

void Controller::AddLayerButtonClicked()
{
	model->CreateLayer();
}

void Controller::DeleteLayerButtonClicked()
{
	model->DeleteActiveLayer();
}

void Controller::MoveLayerUpButtonClicked()
{
	model->MoveActiveLayer(LayerMoveDirection::Down);
}

void Controller::MoveLayerDownButtonClicked()
{
	model->MoveActiveLayer(LayerMoveDirection::Down);
}
