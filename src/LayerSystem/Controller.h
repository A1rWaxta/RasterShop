//
// Created by waxta on 1/1/20.
//

#pragma once

#include <QGridLayout>
#include <QPushButton>

namespace LayerSystem
{
	class Controller : public QGridLayout
	{
	Q_OBJECT

	public:
		Controller(LayerSystemModel& model, LayerSystemView& view);

	private:
		QPushButton* addLayer;
		QPushButton* deleteLayer;
		QPushButton* moveLayerUp;
		QPushButton* moveLayerDown;
		LayerSystemModel& model;
		LayerSystemView& view;
	};
}