#pragma once

#include <QtWidgets>
#include "WorkSpace.h"
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
	void ActiveLayerChanged(LayerPreview* layer);

private:
	enum class LayerMoveDirection
	{
		Up, Down
	};

	void ClearScene();
	void closeEvent(QCloseEvent* closeEvent) override;
	void resizeEvent(QResizeEvent* resizeEvent) override;
	void moveEvent(QMoveEvent* moveEvent) override;
	void keyPressEvent(QKeyEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void CreateScene(int width, int height);
	void ConnectMenuBarActionsToSlots();
	void ShowLayerDeleteConfirmationDialog();
	void CreateShortcuts();
	GraphicsScene* graphicsScene;
	std::vector<LayerPreview*> layers;
	LayerPreview* activeLayer;
	int layersAddedCount;
	QShortcut* ctrlC;
	QShortcut* ctrlV;
	QShortcut* del;
	Ui::MainWindow* ui;
};