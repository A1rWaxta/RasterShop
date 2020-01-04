//
// Created by waxta on 1/1/20.
//

#pragma once

#include <QWidget>
#include "Controller.h"
#include "Model.h"
#include "View.h"

namespace LayerSystem
{
	class LayerSystemMain : public QWidget
	{
	public:
		LayerSystemMain();

	private:
		Controller* controller;
		View* view;
		Model* model;
	};
}
