#include "MainWindowX.h"
#include "ui_MainWindowX.h"

MainWindowX::MainWindowX(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowX)
{
    ui->setupUi(this);
	menuBar = new QMenuBar(this);
	QMenu * fileMenu = menuBar->addMenu(tr("&Plik"));
	QAction *newAct = new QAction(tr("&New"), this);
	fileMenu->addAction(newAct);
	menuBar->setStyleSheet("background-color: black; color: white;");
}

MainWindowX::~MainWindowX()
{
    delete ui;
}

void MainWindowX::closeEvent(QCloseEvent *closeEvent)
{
	QWidget::closeEvent(closeEvent);
}

void MainWindowX::Show()
{

}

void MainWindowX::resizeEvent(QResizeEvent *resizeEvent)
{
	menuBar->resize(resizeEvent->size().width(), menuBar->size().height());
}
