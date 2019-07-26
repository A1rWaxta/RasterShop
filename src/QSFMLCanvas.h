#pragma once

#include <SFML/Graphics.hpp>
#include <QtCore/QTimer>
#include <QtWidgets/QWidget>

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
public:
	QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime = 0);
	virtual ~QSFMLCanvas();

private:
	virtual void OnInit();
	virtual void OnUpdate();
	virtual QPaintEngine* paintEngine() const;
	virtual void showEvent(QShowEvent*);
	virtual void paintEvent(QPaintEvent*);

	QTimer myTimer;
	bool myInitialized;
	QSize canvasSize;
};