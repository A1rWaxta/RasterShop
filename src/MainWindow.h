#pragma once

#include <QtWidgets>
#include "Canvas.h"
#include "GraphicsScene.h"
#include "LayerPreview.h"

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

	void CreateLayer();

	void LayerSelected(LayerPreview* layer);

private:
	void closeEvent(QCloseEvent* closeEvent) override;

	void resizeEvent(QResizeEvent* resizeEvent) override;

	void moveEvent(QMoveEvent* moveEvent) override;

	void keyPressEvent(QKeyEvent* event) override;

	void mouseReleaseEvent(QMouseEvent* event) override;

	void CreateLayerPreview(ImageLayer* layer);

	void DeleteActiveLayer();

	QSharedPointer<GraphicsScene> graphicsScene;

	QMap<QString, ImageLayer*> layers;

	LayerPreview* activeLayer;

	Ui::MainWindow* ui;
};