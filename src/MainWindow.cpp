#include "MainWindow.h"
#include "ui_MainWindowX.h"
#include "NewProjectDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    centralWidget(new QWidget(this))
{
	QSettings settings;
	int width, height;
	int xPos, yPos;

	ui->setupUi(this);

	toolBar = new ToolBar(this);

    width = qApp->screens()[0]->size().width() / 2;
    height = qApp->screens()[0]->size().height() / 2;
    width = settings.value("window/width", width).toInt();
    height = settings.value("window/height", height).toInt();
    xPos = settings.value("window/xpos", 0).toInt();
    yPos = settings.value("window/ypos", 0).toInt();

    setGeometry(xPos, yPos, width, height);
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
}

void MainWindow::FirstButtonClicked()
{
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
}
