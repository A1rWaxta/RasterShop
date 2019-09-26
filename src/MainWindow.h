//
// Created by waxta on 15.09.19.
//

#pragma once


#include <QtWidgets>

class MainWindow : public QMainWindow
{
public:
	MainWindow();

	virtual ~MainWindow();

	void Show();

private:
	void resizeEvent(QResizeEvent * resizeEvent) override;

	QMenuBar * menuBar;

	void closeEvent(QCloseEvent * closeEvent) override;
};


