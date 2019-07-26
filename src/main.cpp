#include <SFML/Graphics.hpp>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include "MyCanvas.h"
#include "MainWindow.h"

int main(int argc, char **argv)
{
	QApplication App(argc, argv);

	/*QFrame* MainFrame = new QFrame;
	MainFrame->setWindowTitle("Qt SFML");
	MainFrame->resize(1024, 768);
	MainFrame->show();

	MyCanvas* SFMLView = new MyCanvas(MainFrame, QPoint(0, 0), QSize(1024, 768));
	SFMLView->show();*/

	MainWindow window;
	window.show();

	return App.exec();
}