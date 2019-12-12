#include "ToolBar.h"
#include "ui_ToolBar.h"
#include <QDebug>

ToolBar::ToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBar)
{
    ui->setupUi(this);
    layout()->setAlignment(Qt::AlignTop);

	qRegisterMetaType<ActiveTool>("ActiveTool");

    connect(ui->selectToolButton, &QPushButton::released, this, &ToolBar::SelectionToolSelected);
	connect(ui->moveToolButton, &QPushButton::released, this, &ToolBar::MoveToolSelected);
}

ToolBar::~ToolBar()
{
    delete ui;
}

void ToolBar::SelectionToolSelected()
{
	emit ToolSelected(ActiveTool::Selection);
}

void ToolBar::MoveToolSelected()
{
	emit ToolSelected(ActiveTool::Move);
}