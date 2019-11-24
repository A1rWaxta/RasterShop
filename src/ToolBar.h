//
// Created by waxta on 21.11.19.
//

#pragma once

#include <QtWidgets>
#include "ToolBarButton.h"

class ToolBar : public QWidget
{
	Q_OBJECT

public:
	explicit ToolBar(QWidget * parent = nullptr);

	[[nodiscard]] QSize sizeHint() const override;

	void CreateButton(QIcon &icon);

private slots:
	void ButtonPressed();

private:
	std::vector<ToolBarButton*> buttons;

	void paintEvent(QPaintEvent * event) override;


};


