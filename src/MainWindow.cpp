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

	ui->addLayerButton->setDisabled(true);

	connect(ui->actionNew, &QAction::triggered, this, &MainWindow::NewActionClicked);
	connect(ui->actionSave, &QAction::triggered, this, &MainWindow::SaveActionClicked);
	connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::SaveAsActionClicked);
	connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::OpenActionClicked);
	connect(ui->addLayerButton, &QPushButton::released, this, &MainWindow::CreateLayer);
	connect(ui->deleteLayerButton, &QPushButton::released, this, &MainWindow::DeleteActiveLayer);
}

MainWindow::~MainWindow()
{
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

void MainWindow::Show()
{
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
		if( menu->isVisible() == true )
		{
			menu->hide();
			return;
		}
	}
}

void MainWindow::CreateNewProject()
{
}

void MainWindow::NewCanvas(const QString& string)
{
}

void MainWindow::FirstButtonClicked()
{
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
}

void MainWindow::OpenActionClicked()
{
	QFileDialog fileDialog;
	fileDialog.resize(320, 100);
	fileDialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
	fileDialog.setFileMode(QFileDialog::ExistingFile);

	QStringList fileNames;
	if( fileDialog.exec() == QFileDialog::Accepted )
	{
		fileNames = fileDialog.selectedFiles();

	}
}

void MainWindow::SaveAsActionClicked()
{
//	canvas = new Canvas(this, QPoint(100, 100), QSize(100, 100));
}

void MainWindow::SaveActionClicked()
{

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

		if( graphicsScene != nullptr )
		{
			graphicsScene.reset();
			graphicsScene = nullptr;
		}
		layers.clear();
		graphicsScene = QSharedPointer<GraphicsScene>(new GraphicsScene(this));
		graphicsScene->setSceneRect(0, 0, canvasWidth, canvasHeight);
		ui->canvas->setScene(graphicsScene.data());

		//spaghetti starts... yummy :)
		CreateLayer();

		auto backgroundRectangle = new QGraphicsRectItem(0, 0, canvasWidth, canvasHeight);
		backgroundRectangle->setPen(QPen(Qt::NoPen));
		backgroundRectangle->setBrush(QBrush(backgroundColor));
		graphicsScene->AddItemOnActiveLayer(backgroundRectangle);

		graphicsScene->update();
		ui->canvas->update();

		ui->addLayerButton->setDisabled(false);
	}
}

void MainWindow::CreateLayer()
{
	QString layerName = "layer_" + QString::number(layers.size());

	auto newLayer = new ImageLayer(layerName);
	newLayer->setZValue(layers.size());
	layers[layerName] = newLayer;
	graphicsScene->addItem(newLayer);

	CreateLayerPreview(newLayer);
}

void MainWindow::CreateLayerPreview(ImageLayer* layer)
{
	//todo: mapować String-LayerPreview* zamiast String-ImageLayer*
	auto layerPreview = new LayerPreview(layer, ui->scrollAreaWidgetContents);
	auto layout = dynamic_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
	layout->setAlignment(Qt::AlignTop);
	layout->addWidget(layerPreview, layout->count());

	connect(layerPreview, &LayerPreview::LayerSelected, this, &MainWindow::LayerSelected);

	LayerSelected(layerPreview);
}

void MainWindow::LayerSelected(LayerPreview* layer)
{
	if( activeLayer == layer )
	{
		return;
	}
	if( activeLayer != nullptr )
	{
		activeLayer->Unselect();
	}
	activeLayer = layer;
	activeLayer->Select();
	graphicsScene->SetActiveLayer(activeLayer->GetLayer());
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	if( event->key() == Qt::Key_Delete )
	{

		DeleteActiveLayer();
	}
}

void MainWindow::DeleteActiveLayer()
{
	if( activeLayer != nullptr )
	{
		QMessageBox confirmationDialog;
		confirmationDialog.setText(tr("Usunąć warstwe ") + activeLayer->GetLayer()->GetIdentifier() + "?");
		confirmationDialog.addButton(tr("Nie"), QMessageBox::ButtonRole::RejectRole);
		confirmationDialog.addButton(tr("Tak"), QMessageBox::ButtonRole::AcceptRole);
		if( confirmationDialog.exec() == QMessageBox::Accepted )
		{
			delete activeLayer;
			activeLayer = nullptr;
		}
	}
}