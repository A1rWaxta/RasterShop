//
// Created by waxta on 1/1/20.
//

#pragma once

#include <QGridLayout>
#include <QPushButton>
#include "View.h"
#include "Model.h"

namespace LayerSystem
{
	class Controller : public QGridLayout
	{
	Q_OBJECT

	public:
		Controller(Model* model, View* view);

	private slots:
		void AddLayerButtonClicked();
		void DeleteLayerButtonCliked();
		void MoveLayerUpButtonClicked();
		void MoveLayerDownButtonClicked();

	private:
		QPushButton* addLayer;
		QPushButton* deleteLayer;
		QPushButton* moveLayerUp;
		QPushButton* moveLayerDown;
		Model* model;
		View* view;
	};
}