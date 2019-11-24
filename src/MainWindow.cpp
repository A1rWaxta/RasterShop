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

	setMinimumSize(740, 600);

	ui->setupUi(this);

	toolBar = new ToolBar(this);

    width = qApp->screens()[0]->size().width() / 2;
    height = qApp->screens()[0]->size().height() / 2;
    width = settings.value("window/width", width).toInt();
    height = settings.value("window/height", height).toInt();
    xPos = settings.value("window/xpos", 0).toInt();
    yPos = settings.value("window/ypos", 0).toInt();
    setGeometry(xPos, yPos, width, height);

    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::NewActionClicked);
	connect(ui->actionSave, &QAction::triggered, this, &MainWindow::SaveActionClicked);
	connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::SaveAsActionClicked);
	connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::OpenActionClicked);
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
	QList<QMenu*> menuList;
	menuList = ui->menuBar->findChildren<QMenu*>();
	for(QMenu * menu : menuList)
	{
		if( menu->isVisible() == true )
		{
			menu->hide();
			return;
		}
	}
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

void MainWindow::OpenActionClicked()
{
	QFileDialog fileDialog;
	fileDialog.resize(320, 100);
	fileDialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
	fileDialog.setFileMode(QFileDialog::ExistingFile);

	QStringList fileNames;
	if( fileDialog.exec() )
	{
		fileNames = fileDialog.selectedFiles();
	}
}

void MainWindow::SaveAsActionClicked()
{

}

void MainWindow::SaveActionClicked()
{

}

void MainWindow::NewActionClicked()
{

}
