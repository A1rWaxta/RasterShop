//
// Created by waxta on 1/1/20.
//

#include "Controller.h"
#include "Globals.h"

using LayerSystem::Controller;

Controller::Controller(Model* model, View* view) : model(model), view(view)
{
	addLayer = new QPushButton();
	addLayer->setText(tr("Dodaj"));

	deleteLayer = new QPushButton();
	deleteLayer->setText(tr("Usuń"));

	moveLayerUp = new QPushButton();
	moveLayerUp->setText(tr("Góra"));

	moveLayerDown = new QPushButton();
	moveLayerDown->setText(tr("Dół"));

	addWidget(addLayer);
	addWidget(deleteLayer);
	addWidget(moveLayerUp);
	addWidget(moveLayerDown);

	connect(addLayer, &QPushButton::released, this, &Controller::AddLayerButtonClicked);
	connect(deleteLayer, &QPushButton::released, this, &Controller::DeleteLayerButtonCliked);
	connect(moveLayerDown, &QPushButton::released, this, &Controller::MoveLayerDownButtonClicked);
	connect(moveLayerUp, &QPushButton::released, this, &Controller::MoveLayerUpButtonClicked);
}

void Controller::AddLayerButtonClicked()
{
	model->CreateImageLayer();
}

void Controller::DeleteLayerButtonCliked()
{
	model->DeleteActiveLayer();
}

void Controller::MoveLayerUpButtonClicked()
{
	model->MoveActiveLayer(LayerMoveDirection::Up);
}

void Controller::MoveLayerDownButtonClicked()
{
	model->MoveActiveLayer(LayerMoveDirection::Down);
}
