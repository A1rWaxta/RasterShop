#pragma once

#include "QSFMLCanvas.h"

class MyCanvas : public QSFMLCanvas
{
public:
	MyCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
			QSFMLCanvas(Parent, Position, Size)
	{

	}

private:
	void OnInit()
	{

	}
	void OnUpdate()
	{
		sf::RenderWindow::clear(sf::Color::Red);
	}
};


