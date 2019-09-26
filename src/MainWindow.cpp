//
// Created by waxta on 15.09.19.
//

#include <iostream>
#include "MainWindow.h"
#include "ApplicationSettings.h"

void MainWindow::resizeEvent(QResizeEvent *resizeEvent)
{
	QWidget::resizeEvent(resizeEvent);
}

MainWindow::MainWindow()
{
}

MainWindow::~MainWindow()
{
	std::cout << "Destruktor\n";
}

void MainWindow::Show()
{
	QSettings settings;
	if(settings.contains("window/width") == true && settings.contains("window/height") == true)
	{
		resize(settings.value("window/width").toInt(), settings.value("window/height").toInt());
	}
	if(settings.contains("window/title") == true)
	{
		setWindowTitle(settings.value("window/title").toString());
	}

	menuBar = new QMenuBar(this);
	QMenu * fileMenu = menuBar->addMenu(tr("&Plik"));
	QAction *newAct = new QAction(tr("&New"), this);
	fileMenu->addAction(newAct);
	menuBar->setStyleSheet("background-color: black; color: white;");
	menuBar->show();

	QMainWindow::show();
}

void MainWindow::closeEvent(QCloseEvent *closeEvent)
{
	QSettings settings;
	settings.setValue("window/width", width());
	settings.setValue("window/height", height());
	settings.sync();
}