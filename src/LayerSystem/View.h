//
// Created by waxta on 1/1/20.
//

#pragma once

#include <QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include "Model.h"

namespace LayerSystem
{
	class View : public QScrollArea
	{
	public:
		View();
		void Update();
		void ObserveLayerModel(Model* model);

	private:
		QVBoxLayout* layout;
		Model* model;
	};
}