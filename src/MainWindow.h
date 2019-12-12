#pragma once

#include <QtWidgets>
#include "Canvas.h"
#include "LayerPreview.h"
#include "Globals.h"
#include "GraphicsScene.h"

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);

	~MainWindow() override;

private slots:
	void NewActionClicked();

	void NewCanvas();

	void FirstButtonClicked();

	void OpenActionClicked();

	void SaveAsActionClicked();

	void SaveActionClicked();

	void InitializeNewProject(int width, int height);

	void CreateLayer();

	void SelectActiveLayer(LayerPreview* layer);

	void MoveLayerUp();

	void MoveLayerDown();

private:
	enum class LayerMoveDirection
	{
		Up,
		Down
	};

	void MoveLayer(LayerMoveDirection direction);

	void closeEvent(QCloseEvent* closeEvent) override;

	void resizeEvent(QResizeEvent* resizeEvent) override;

	void moveEvent(QMoveEvent* moveEvent) override;

	void keyPressEvent(QKeyEvent* event) override;

	void mouseReleaseEvent(QMouseEvent* event) override;

	void DeleteActiveLayer();

	std::shared_ptr<GraphicsScene> graphicsScene;

	std::vector<LayerPreview*> layers;

	LayerPreview* activeLayer;

	int layersAddedCount;

	Ui::MainWindow* ui;
};