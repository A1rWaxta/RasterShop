#include "ToolBar.h"
#include "ui_ToolBar.h"
#include <QDebug>

ToolBar::ToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBar)
{
    ui->setupUi(this);
    layout()->setAlignment(Qt::AlignTop);

    connect(ui->selectToolButton, &QPushButton::released, this, &ToolBar::SelectionToolSelected);
	connect(ui->moveToolButton, &QPushButton::released, this, &ToolBar::MoveToolSelected);
	connect(ui->penToolButton, &QPushButton::released, this, &ToolBar::PenToolSelected);
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

void ToolBar::PenToolSelected()
{
	//todo: parameter tab must appears when this option is selected
	emit ToolSelected(ActiveTool::Pen);
}