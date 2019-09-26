//
// Created by waxta on 13.07.19.
//

#pragma once

#include <QtWidgets>
#include "Canvas.h"
#include "ApplicationSettings.h"

class MainWindow : public QWidget
{
public:
	MainWindow();

	~MainWindow() override;

	void show();

private slots:
	void OpenFile();

private:
	void CreateActions();

	std::shared_ptr<Canvas> myCanv;

	const std::shared_ptr<ApplicationSettings> appSettings;
};