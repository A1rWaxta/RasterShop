#include "MainWindow.h"
#include "ui_MainWindowX.h"
#include "NewProjectDialog.h"

MainWindow::MainWindow(QWidget *parent) :
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

	connect(newAct, &QAction::triggered, this, &MainWindow::CreateNewProject);

	label = findChild<QLabel*>("label");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *closeEvent)
{
	QSettings settings;
	settings.setValue("window/width", width());
	settings.setValue("window/height", height());
	settings.setValue("window/xpos", pos().x());
	settings.setValue("window/ypos", pos().y());
	settings.sync();
}

void MainWindow::Show()
{

}

void MainWindow::resizeEvent(QResizeEvent *resizeEvent)
{
	menuBar->resize(resizeEvent->size().width(), menuBar->size().height());
}

void MainWindow::moveEvent(QMoveEvent *moveEvent)
{
}

void MainWindow::CreateNewProject()
{
	NewProjectDialog XD;
	connect(&XD, &NewProjectDialog::DialogAccepted, this, &MainWindow::NewCanvas);
	XD.exec();
}

void MainWindow::NewCanvas(const QString & string)
{
	label->setText(string);
}
