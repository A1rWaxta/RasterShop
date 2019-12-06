#pragma once

#include <QtWidgets>
#include "Canvas.h"
#include "GraphicsScene.h"

namespace Ui
{
	class MainWindow;
}

// this is definitely going to be The Blob antipattern...
class MainWindow : public QMainWindow
{
Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);

	~MainWindow() override;

	void Show();

private slots:

	void CreateNewProject();

	void NewCanvas(const QString& string);

	void FirstButtonClicked();

	void OpenActionClicked();

	void SaveAsActionClicked();

	void SaveActionClicked();

	void NewActionClicked();

private:
	void closeEvent(QCloseEvent* closeEvent) override;

	void resizeEvent(QResizeEvent* resizeEvent) override;

	void moveEvent(QMoveEvent* moveEvent) override;

	void mouseReleaseEvent(QMouseEvent* event) override;

	QSharedPointer<GraphicsScene> graphicsScene;

	QVector<ImageLayer> layers;

	Ui::MainWindow* ui;
};