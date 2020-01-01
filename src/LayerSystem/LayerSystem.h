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
	class LayerSystem : public QWidget
	{
	public:


	private:
		LayerSystemConstroller* controller;
		View* view;
		Model* model;
	};
}
