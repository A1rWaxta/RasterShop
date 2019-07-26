//
// Created by waxta on 13.07.19.
//

#include <QtWidgets/QDialog>
#include "MainWindow.h"

MainWindow::MainWindow()
{
	resize(1024, 768);
	setWindowTitle("RasterShop");

	canvas = new MyCanvas(this, QPoint(100, 100), QSize(640, 480));
	canvas->show();
}

MainWindow::~MainWindow()
{
	delete canvas;
}