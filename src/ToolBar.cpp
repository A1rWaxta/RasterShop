//
// Created by waxta on 21.11.19.
//

#include "ToolBar.h"
#include <QDebug>

namespace
{
	constexpr auto BUTTON_HEIGHT = 50;
	constexpr auto BUTTON_WIDTH = 50;
	constexpr auto TOOLBAR_WIDTH = 57;
	constexpr auto TOOLBAR_HEIGHT = 70;
	constexpr auto BUTTON_BOTTOM_SPACING = 10;
}

ToolBar::ToolBar(QWidget * parent) : QWidget(parent), buttons(0)
{
	setGeometry(0, 50, TOOLBAR_WIDTH, TOOLBAR_HEIGHT);

	QPixmap img("res/paint.png");
	QIcon icon(img);

	CreateButton(icon);
	connect(buttons.back(), &QPushButton::clicked, this, &ToolBar::ButtonPressed);

	CreateButton(icon);
	connect(buttons.back(), &QPushButton::clicked, this, &ToolBar::ButtonPressed);

	CreateButton(icon);
	connect(buttons.back(), &QPushButton::clicked, this, &ToolBar::ButtonPressed);

	for(ToolBarButton * button : buttons)
	{
		button->setIconSize(QSize(30, 30));
	}
}

void ToolBar::CreateButton(QIcon &icon)
{
	const static int xPos = (TOOLBAR_WIDTH / 2) - (BUTTON_WIDTH / 2);

	resize(TOOLBAR_WIDTH, height() + BUTTON_HEIGHT);

	buttons.push_back(new ToolBarButton(this));
	buttons.back()->setGeometry(
			xPos,
			(BUTTON_HEIGHT * (buttons.size() - 1)) + TOOLBAR_HEIGHT / 2 + (buttons.size() - 1) * BUTTON_BOTTOM_SPACING,
			BUTTON_WIDTH,
			BUTTON_HEIGHT
			);
	buttons.back()->setIcon(icon);

	update();
}

void ToolBar::ButtonPressed()
{
}

QSize ToolBar::sizeHint() const
{
	return QSize(400, 400);
}

void ToolBar::paintEvent(QPaintEvent *event)
{
//	QPainter p(this);
//	QBrush brush(QColor(42, 47, 87));
//	p.fillRect(QRect(0, 0, width(), height()), brush);
}