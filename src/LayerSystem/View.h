//
// Created by waxta on 1/1/20.
//

#pragma once

#include <QScrollArea>
#include <QtWidgets/QVBoxLayout>

namespace LayerSystem
{
	class View : public QScrollArea
	{
	public:
		View();
		void Update();

	private:
		QVBoxLayout* layout;
	};
}