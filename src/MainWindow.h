#pragma once

#include <QtWidgets>
#include "ToolBar.h"
#include "Canvas.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    
    ~MainWindow();

    void Show();

private slots:
	void CreateNewProject();

	void NewCanvas(const QString & string);

	void FirstButtonClicked();

	void OpenActionClicked();

	void SaveAsActionClicked();

	void SaveActionClicked();

	void NewActionClicked();

private:
	void closeEvent(QCloseEvent * closeEvent) override;

	void resizeEvent(QResizeEvent * resizeEvent) override;

	void moveEvent(QMoveEvent * moveEvent) override;

	void mouseReleaseEvent(QMouseEvent * event) override;

	Ui::MainWindow * ui;

	ToolBar * toolBar;

	QWidget * centralWidget;

	Canvas * canvas;
};