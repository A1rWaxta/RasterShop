//
// Created by waxta on 1/1/20.
//

#include "LayerSystemMain.h"

using LayerSystem::LayerSystemMain;

LayerSystemMain::LayerSystemMain()
{
	view = new View();
	model = new Model();
	model->AttachView(view);
	controller = new Controller(model, view);
	view->setParent(this);
	controller->setParent(this);
	//todo: let user choose which model, view observes
}
