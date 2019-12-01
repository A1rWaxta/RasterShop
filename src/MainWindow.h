#pragma once

#include <QtWidgets>
#include "Canvas.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    
    ~MainWindow() override;

    void Show();

private slots:
	void CreateNewProject();

	void NewCanvas(const QString & string);

	void FirstButtonClicked();

	void OpenActionClicked();

	void SaveAsActionClicked();

	void SaveActionClicked();

	void NewActionClicked();

	void CreateCanvas(int width, int height, QColor color);

private:
	void closeEvent(QCloseEvent * closeEvent) override;

	void resizeEvent(QResizeEvent * resizeEvent) override;

	void moveEvent(QMoveEvent * moveEvent) override;

	void mouseReleaseEvent(QMouseEvent * event) override;

	Ui::MainWindow * ui;

	QWidget * centralWidget;
};