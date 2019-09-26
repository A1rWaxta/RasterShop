//
// Created by waxta on 13.07.19.
//

#pragma once

#include <QtWidgets>
#include "Canvas.h"
#include "ApplicationSettings.h"
#include "MainWindow.h"

class UserInterface : public QWidget
{
public:
	UserInterface();

	~UserInterface();

	void Show();

	bool LoadUIFile();

private slots:
	void OpenFile();

private:
	void CreateActions();

	QWidget * userInterface;

	std::shared_ptr<Canvas> myCanv;

	MainWindow * mainWindow;

	const std::shared_ptr<ApplicationSettings> appSettings;
};