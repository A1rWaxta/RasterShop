#include "QSFMLCanvas.h"

QSFMLCanvas::QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime) :
		QWidget       (Parent),
		myInitialized (false),
		canvasSize(Size)
{
	// Setup some states to allow direct rendering into the widget
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_OpaquePaintEvent);
	setAttribute(Qt::WA_NoSystemBackground);

	// Set strong focus to enable keyboard events to be received
	setFocusPolicy(Qt::StrongFocus);

	// Setup the widget geometry
	move(Position);

	// Setup the timer
	myTimer.setInterval(FrameTime);
}

void QSFMLCanvas::showEvent(QShowEvent*)
{
	if (!myInitialized)
	{
		// Under X11, we need to flush the commands sent to the server to ensure that
		// SFML will get an updated view of the windows
#ifdef Q_WS_X11
		XFlush(QX11Info::display());
#endif
		// Create the SFML window with the widget handle
		sf::RenderWindow::create((sf::WindowHandle) winId());
		sf::RenderWindow::setSize(sf::Vector2u(canvasSize.width(), canvasSize.height()));

		this->OnInit();

		// Setup the timer to trigger a refresh at specified framerate
		connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));
		myTimer.start();

		myInitialized = true;
	}
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
	return 0;
}

void QSFMLCanvas::paintEvent(QPaintEvent*)
{
	this->OnUpdate();

	sf::RenderWindow::display();
}

QSFMLCanvas::~QSFMLCanvas() {}
void QSFMLCanvas::OnInit() {}
void QSFMLCanvas::OnUpdate() {}