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

signals:
	void ToolSelected(ActiveTool tool);

private:
	QShortcut* shortcutS;
	QShortcut* shortcutM;
	QShortcut* shortcutP;
	QShortcut* shortcutB;
	QShortcut* shortcutR;
	QShortcut* shortcutT;
	QShortcut* shiftS;
	QShortcut* shiftB;
	ToolBarButton* checkedButton;
	QBrush activeToolBrush;
	ToolBarButton* active;
	Ui::ToolBar* ui;
	void PolygonToolSelected();
	void CreateShortcuts();
};