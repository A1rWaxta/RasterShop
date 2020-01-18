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
	CreateShortcuts();

	checkedButton = ui->selectToolButton;

	activeToolBrush.setColor(QColor(145, 102, 144));

	QPixmap pixmap;

	//SELECT TOOL
	pixmap.load("res/arrow.svg");
	QIcon selectionTooIcon(pixmap);
	ui->selectToolButton->setIcon(selectionTooIcon);
	ui->selectToolButton->setIconSize(QSize(40, 40));
	connect(ui->selectToolButton, &QPushButton::released, [this](){
		checkedButton->setChecked(false);
		checkedButton = ui->selectToolButton;
		ui->selectToolButton->setChecked(true);
		emit ToolSelected(ActiveTool::Selection);
	});

	//MOVE TOOL
	pixmap.load("res/move-arrows.svg");
	QIcon moveToolIcon(pixmap);
	ui->moveToolButton->setIcon(moveToolIcon);
	ui->moveToolButton->setIconSize(QSize(42, 42));
	connect(ui->moveToolButton, &QPushButton::released, [this](){
		checkedButton->setChecked(false);
		checkedButton = ui->moveToolButton;
		ui->moveToolButton->setChecked(true);
		emit ToolSelected(ActiveTool::Move);
	});

	//PEN TOOL
	pixmap.load("res/brush.svg");
	QIcon brushToolIcon(pixmap);
	ui->penToolButton->setIcon(brushToolIcon);
	ui->penToolButton->setIconSize(QSize(45, 45));
	connect(ui->penToolButton, &QPushButton::released, [this](){
		checkedButton->setChecked(false);
		checkedButton = ui->penToolButton;
		ui->penToolButton->setChecked(true);
		emit ToolSelected(ActiveTool::Pen);
	});

	//BUCKET TOOL
	pixmap.load("res/bucket.svg");
	QIcon paintToolIcon(pixmap);
	ui->paintToolButton->setIcon(paintToolIcon);
	ui->paintToolButton->setIconSize(QSize(45, 45));
	connect(ui->paintToolButton, &QPushButton::released, [this](){
		checkedButton->setChecked(false);
		checkedButton = ui->paintToolButton;
		ui->paintToolButton->setChecked(true);
		emit ToolSelected(ActiveTool::Paint);
	});

	//SCALE TOOL
	pixmap.load("res/scale.svg");
	QIcon scaleToolIcon(pixmap);
	ui->scaleToolButton->setIcon(scaleToolIcon);
	ui->scaleToolButton->setIconSize(QSize(45, 45));
	connect(ui->scaleToolButton, &QPushButton::released, [this](){
		checkedButton->setChecked(false);
		checkedButton = ui->scaleToolButton;
		ui->scaleToolButton->setChecked(true);
		emit ToolSelected(ActiveTool::Scale);
	});

	//ROTATION TOOL
	pixmap.load("res/rotate.svg");
	QIcon rotateToolIcon(pixmap);
	ui->rotationToolButton->setIcon(rotateToolIcon);
	ui->rotationToolButton->setIconSize(QSize(45, 45));
	connect(ui->rotationToolButton, &QPushButton::released, [this](){
		checkedButton->setChecked(false);
		checkedButton = ui->rotationToolButton;
		ui->rotationToolButton->setChecked(true);
		emit ToolSelected(ActiveTool::Rotation);
	});

	//TEXT TOOL
	pixmap.load("res/text.svg");
	QIcon textToolIcon(pixmap);
	ui->textToolButton->setIcon(textToolIcon);
	ui->textToolButton->setIconSize(QSize(45, 45));
	connect(ui->textToolButton, &QPushButton::released, [this](){
		checkedButton->setChecked(false);
		checkedButton = ui->textToolButton;
		ui->textToolButton->setChecked(true);
		emit ToolSelected(ActiveTool::Text);
	});

	//POLYGON TOOL
	pixmap.load("res/polygon.svg");
	QIcon polygonToolIcon(pixmap);
	ui->polygonToolButton->setIcon(polygonToolIcon);
	ui->polygonToolButton->setIconSize(QSize(45, 45));
	connect(ui->polygonToolButton, &QPushButton::released, [this](){
		checkedButton->setChecked(false);
		checkedButton = ui->polygonToolButton;
		ui->polygonToolButton->setChecked(true);
		emit ToolSelected(ActiveTool::Polygon);
	});
}

ToolBar::~ToolBar()
{
	delete ui;
}

void ToolBar::CreateShortcuts()
{
	//SELECT TOOL
	shortcutS = new QShortcut(this);
	shortcutS->setKey(Qt::Key_S);
	connect(shortcutS, &QShortcut::activated, [this](){
		checkedButton->setChecked(false);
		checkedButton = ui->selectToolButton;
		ui->selectToolButton->setChecked(true);
		emit ToolSelected(ActiveTool::Selection);
	});

	//MOVE TOOL
	shortcutM = new QShortcut(this);
	shortcutM->setKey(Qt::Key_M);
	connect(shortcutM, &QShortcut::activated, [this](){
		checkedButton->setChecked(false);
		checkedButton = ui->moveToolButton;
		ui->moveToolButton->setChecked(true);
		emit ToolSelected(ActiveTool::Move);
	});

	//POLYGON TOOL
	shortcutP = new QShortcut(this);
	shortcutP->setKey(Qt::Key_P);
	connect(shortcutP, &QShortcut::activated, [this](){
		checkedButton->setChecked(false);
		checkedButton = ui->polygonToolButton;
		ui->polygonToolButton->setChecked(true);
		emit ToolSelected(ActiveTool::Polygon);
	});

	//BUCKET TOOL
	shortcutB = new QShortcut(this);
	shortcutB->setKey(Qt::Key_B);
	connect(shortcutB, &QShortcut::activated, [this](){
		checkedButton->setChecked(false);
		checkedButton = ui->paintToolButton;
		ui->paintToolButton->setChecked(true);
		emit ToolSelected(ActiveTool::Paint);
	});

	//ROTATION TOOL
	shortcutR = new QShortcut(this);
	shortcutR->setKey(Qt::Key_R);
	connect(shortcutR, &QShortcut::activated, [this](){
		checkedButton->setChecked(false);
		checkedButton = ui->rotationToolButton;
		ui->rotationToolButton->setChecked(true);
		emit ToolSelected(ActiveTool::Rotation);
	});

	//SCALE TOOL
	shiftS = new QShortcut(this);
	shiftS->setKey(Qt::Key_S + Qt::SHIFT);
	connect(shiftS, &QShortcut::activated, [this](){
		checkedButton->setChecked(false);
		checkedButton = ui->scaleToolButton;
		ui->scaleToolButton->setChecked(true);
		emit ToolSelected(ActiveTool::Scale);
	});

	//TEXT TOOL
	shortcutT = new QShortcut(this);
	shortcutT->setKey(Qt::Key_T);
	connect(shortcutT, &QShortcut::activated, [this](){
		checkedButton->setChecked(false);
		checkedButton = ui->textToolButton;
		ui->textToolButton->setChecked(true);
		emit ToolSelected(ActiveTool::Text);
	});

	//PEN TOOL
	shiftB = new QShortcut(this);
	shiftB->setKey(Qt::Key_B + Qt::SHIFT);
	connect(shiftB, &QShortcut::activated, [this](){
		checkedButton->setChecked(false);
		checkedButton = ui->penToolButton;
		ui->penToolButton->setChecked(true);
		emit ToolSelected(ActiveTool::Pen);
	});
}