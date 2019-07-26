//
// Created by waxta on 13.07.19.
//

#pragma once

#include <QtWidgets/QMainWindow>
#include "MyCanvas.h"

class MainWindow : public QMainWindow
{
public:
	MainWindow();
	~MainWindow();

private:
	MyCanvas * canvas;
};


