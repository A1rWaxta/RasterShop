#include "MainWindow.h"
#include "ui_MainWindowX.h"

MainWindowX::MainWindowX(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	QMenu * fileMenu;
	QAction * newAct;
	QSettings settings;
	int width, height;
	int xPos, yPos;

    ui->setupUi(this);

    width = qApp->screens()[0]->size().width() / 2;
    height = qApp->screens()[0]->size().height() / 2;
    width = settings.value("window/width", width).toInt();
    height = settings.value("window/height", height).toInt();
    xPos = settings.value("window/xpos", 0).toInt();
    yPos = settings.value("window/ypos", 0).toInt();

    resize(width, height);
	move(xPos, yPos);

	menuBar = new QMenuBar(this);
	fileMenu = menuBar->addMenu(tr("&Plik"));
	newAct = new QAction(tr("&Zamknij"), this);
	fileMenu->addAction(newAct);
	menuBar->setStyleSheet("background-color: black; color: white;");
}

MainWindowX::~MainWindowX()
{
    delete ui;
}

void MainWindowX::closeEvent(QCloseEvent *closeEvent)
{
	QSettings settings;
	settings.setValue("window/width", width());
	settings.setValue("window/height", height());
	settings.setValue("window/xpos", pos().x());
	settings.setValue("window/ypos", pos().y());
	settings.sync();
}

void MainWindowX::Show()
{

}

void MainWindowX::resizeEvent(QResizeEvent *resizeEvent)
{
	menuBar->resize(resizeEvent->size().width(), menuBar->size().height());
}

void MainWindowX::moveEvent(QMoveEvent *moveEvent)
{
}
