#pragma once

#include <QWidget>
#include "Globals.h"
#include "ToolBarButton.h"
#include "GraphicsScene.h"

namespace Ui
{
	class ToolBar;
}

class ToolBar : public QWidget
{
Q_OBJECT

public:
	explicit ToolBar(QWidget* parent = nullptr);
	~ToolBar();

private slots:
	void SelectionToolSelected();
	void MoveToolSelected();
	void PenToolSelected();
	void PaintToolSelected();

signals:
	void ToolSelected(ActiveTool tool);

private:
	QPalette selectionPalette;
	QPalette normalPalette;
	QBrush activeToolBrush;
	ToolBarButton* active;
	Ui::ToolBar* ui;
	void ScaleToolSelected();
};