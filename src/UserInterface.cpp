//
// Created by waxta on 13.07.19.
//

#include "MainWindow.h"

class QMainWindow;

MainWindow::MainWindow() : appSettings(ApplicationSettings::Instance())
{
}

MainWindow::~MainWindow()
{
}

void MainWindow::CreateActions()
{

}

void MainWindow::OpenFile()
{
	close();
}

void MainWindow::show()
{

}
