//
// Created by waxta on 23.11.19.
//

#pragma once

#include <QtWidgets/QPushButton>

class ToolBarButton : public QPushButton
{
	Q_OBJECT

public:
	explicit ToolBarButton(QWidget *parent);

	void SetToolTip(QString & toolTip);

private:
	void paintEvent(QPaintEvent * paintEvent) override;

	void enterEvent(QEvent * event) override;

	QString toolTip;
};


