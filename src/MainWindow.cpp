#include "MainWindow.h"
#include "ui_MainWindowX.h"
#include "NewCanvasDialog.h"
#include "LayerPreview.h"

MainWindow::MainWindow(QWidget* parent) :
		QMainWindow(parent),
		graphicsScene(nullptr),
		activeLayer(nullptr),
		ui(new Ui::MainWindow)
{
	QSettings settings;
	int width, height;
	int xPos, yPos;

	ui->setupUi(this);

	setMinimumSize(740, 600);

	width = qApp->screens()[0]->size().width() / 2;
	height = qApp->screens()[0]->size().height() / 2;
	width = settings.value("window/width", width).toInt();
	height = settings.value("window/height", height).toInt();
	xPos = settings.value("window/xpos", 0).toInt();
	yPos = settings.value("window/ypos", 0).toInt();
	setGeometry(xPos, yPos, width, height);

	//todo: connect button's slots after creating project
	ConnectMenuBarActionsToSlots();

	main = new LayerSystem::LayerSystemMain();
	ui->layersTab->layout()->addWidget(main);

	CreateShortcuts();
}

void MainWindow::ConnectMenuBarActionsToSlots()
{
	connect(ui->actionNew, &QAction::triggered, this, &MainWindow::NewActionClicked);
	connect(ui->actionSave, &QAction::triggered, this, &MainWindow::SaveActionClicked);
	connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::SaveAsActionClicked);
	connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::OpenActionClicked);
}

MainWindow::~MainWindow()
{
	for( auto layer : layers )
	{
		delete layer;
	}
	layers.clear();
	delete ui;
}

void MainWindow::closeEvent(QCloseEvent* closeEvent)
{
	QSettings settings;
	settings.setValue("window/width", width());
	settings.setValue("window/height", height());
	settings.setValue("window/xpos", pos().x());
	settings.setValue("window/ypos", pos().y());
	settings.sync();
}

void MainWindow::resizeEvent(QResizeEvent* resizeEvent)
{
}

void MainWindow::moveEvent(QMoveEvent* moveEvent)
{
	QList<QMenu*> menuList;
	menuList = ui->menuBar->findChildren<QMenu*>();
	for( QMenu* menu : menuList )
	{
		if( menu->isVisible() )
		{
			menu->hide();
			return;
		}
	}
}

void MainWindow::NewCanvas()
{
}

void MainWindow::FirstButtonClicked()
{
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
}

void MainWindow::SaveAsActionClicked()
{
	QPainter painter;
	if( graphicsScene != nullptr )
	{
		QFileDialog saveFileDialog(this);
		saveFileDialog.setAcceptMode(QFileDialog::AcceptSave);
		saveFileDialog.setNameFilter("*.png *.bmp *.jpg *.jpeg");

		if( saveFileDialog.exec() == QFileDialog::Accepted )
		{
			QStringList file = saveFileDialog.selectedFiles();
			QPixmap image(graphicsScene->sceneRect().width(), graphicsScene->sceneRect().height());
			painter.begin(&image);
			graphicsScene->render(&painter);
			painter.end();
			image.save(file[0]);
		}
	}
}

void MainWindow::SaveActionClicked()
{

}

void MainWindow::OpenActionClicked()
{
	QFileDialog fileDialog(this);

	fileDialog.resize(320, 100);
	fileDialog.setNameFilter(tr("Images (*.png *.bmp *.jpg *.jpeg)"));
	fileDialog.setFileMode(QFileDialog::ExistingFile);

	QStringList fileNames;
	if( fileDialog.exec() == QFileDialog::Accepted )
	{
		fileNames = fileDialog.selectedFiles();
		QImage image(fileNames[0]);

		InitializeNewProject(image.width(), image.height());

		auto graphicsImage = new QGraphicsPixmapItem(QPixmap::fromImage(image));
		graphicsScene->AddItemOnActiveLayer(graphicsImage);
	}
}

void MainWindow::InitializeNewProject(int width, int height)
{
	ClearScene();

	CreateScene(width, height);

//	CreateLayer();

//	ConnectLayerOperationButtonsToSlots();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	if( event->key() == Qt::Key_Delete )
	{
		ShowLayerDeleteConfirmationDialog();
	}
}

void MainWindow::ActiveLayerChanged(LayerPreview* layer)
{
//	if( activeLayer == layer )
//	{
//		return;
//	}
//	if( activeLayer != nullptr )
//	{
//		activeLayer->Unselect();
//	}
//	activeLayer = layer;
//	activeLayer->Select();
}

void MainWindow::NewActionClicked()
{
	int canvasWidth, canvasHeight;
	NewCanvasDialog newCanvasDialog;
	QColor backgroundColor;
	QPen pen;
	QBrush brush;

	if( newCanvasDialog.exec() == QDialog::Accepted )
	{
		canvasWidth = newCanvasDialog.GetCanvasWidth();
		canvasHeight = newCanvasDialog.GetCanvasHeight();
		backgroundColor = newCanvasDialog.GetCanvasColor();

		InitializeNewProject(canvasWidth, canvasHeight);

		auto backgroundRectangle = new QGraphicsRectItem(0, 0, canvasWidth, canvasHeight);
		backgroundRectangle->setBrush(QBrush(backgroundColor));
		graphicsScene->AddItemOnActiveLayer(backgroundRectangle);
	}
}

void MainWindow::ClearScene()
{
//	QLayoutItem* item;
//	if( graphicsScene != nullptr )
//	{
//		while( (item = ui->layerPreviewLayout->takeAt(0)) != nullptr )
//		{
//			delete item->widget();
//			delete item;
//		}
//
//		layers.clear();
//		graphicsScene->clear();
//		graphicsScene = nullptr;
//		activeLayer = nullptr;
//	}
//	layersAddedCount = 0;
}

void MainWindow::CreateScene(int width, int height)
{
	graphicsScene = new GraphicsScene(width, height, this);
	connect(ui->toolBar, &ToolBar::ToolSelected, graphicsScene, &GraphicsScene::ChangeActiveTool);
	connect(ctrlV, &QShortcut::activated, graphicsScene, &GraphicsScene::Paste);

	ui->workSpace->setScene(graphicsScene);
}

void MainWindow::ShowLayerDeleteConfirmationDialog()
{
	if( activeLayer != nullptr )
	{
		QMessageBox confirmationDialog;
		confirmationDialog.setText(tr("Usunąć warstwę ") + activeLayer->GetLayerName() + "?");
		confirmationDialog.addButton(tr("Nie"), QMessageBox::ButtonRole::RejectRole);
		confirmationDialog.addButton(tr("Tak"), QMessageBox::ButtonRole::AcceptRole);

		if( confirmationDialog.exec() == QMessageBox::Accepted )
		{
//			DeleteActiveLayer();
		}
	}
}

void MainWindow::CreateShortcuts()
{
	ctrlV = new QShortcut(this);
	ctrlV->setKey(QKeySequence::Paste); //ctrl + v

	ctrlC = new QShortcut(this);
	ctrlC->setKey(QKeySequence::Copy);  //ctrl + c

	del = new QShortcut(this);
	del->setKey(QKeySequence::Delete);
}
