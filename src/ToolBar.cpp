#include "ToolBar.h"
#include "ui_ToolBar.h"
#include <QDebug>

ToolBar::ToolBar(QWidget* parent) :
		QWidget(parent),
		active(nullptr),
		ui(new Ui::ToolBar)
{
	ui->setupUi(this);
	layout()->setAlignment(Qt::AlignTop);
	setAutoFillBackground(true);

	connect(ui->selectToolButton, &QPushButton::released, this, &ToolBar::SelectionToolSelected);
	connect(ui->moveToolButton, &QPushButton::released, this, &ToolBar::MoveToolSelected);
	connect(ui->penToolButton, &QPushButton::released, this, &ToolBar::PenToolSelected);
	connect(ui->rectangleToolButton, &QPushButton::released, this, &ToolBar::RectangleShapeSelected);

	activeToolBrush.setColor(QColor(145, 102, 144));

	QPixmap pixmap;

	pixmap.load("res/arrow.svg");
	QIcon selectionTooIcon(pixmap);
	ui->selectToolButton->setIcon(selectionTooIcon);
	ui->selectToolButton->setIconSize(QSize(40, 40));
	ui->selectToolButton->setToolTip("Selection tool");

	pixmap.load("res/move-arrows.svg");
	QIcon moveToolIcon(pixmap);
	ui->moveToolButton->setIcon(moveToolIcon);
	ui->moveToolButton->setIconSize(QSize(42, 42));
	ui->moveToolButton->setToolTip("Move tool");

	pixmap.load("res/brush.svg");
	QIcon brushToolIcon(pixmap);
	ui->penToolButton->setIcon(brushToolIcon);
	ui->penToolButton->setIconSize(QSize(45, 45));
	ui->penToolButton->setToolTip("Pen tool");

	pixmap.load("res/rectangle.svg");
	QIcon rectangleToolIcon(pixmap);
	ui->rectangleToolButton->setIcon(rectangleToolIcon);
	ui->rectangleToolButton->setIconSize(QSize(45, 45));
	ui->rectangleToolButton->setToolTip("Rectangle tool");

	pixmap.load("res/scale.svg");
	QIcon scaleToolIcon(pixmap);
	ui->scaleToolButton->setIcon(scaleToolIcon);
	ui->scaleToolButton->setIconSize(QSize(45, 45));
	ui->scaleToolButton->setToolTip("Scale tool");
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
	emit ToolSelected(ActiveTool::Pen);
}

void ToolBar::RectangleShapeSelected()
{
	emit ToolSelected(ActiveTool::RectangleShape);
}