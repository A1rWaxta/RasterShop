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
	ui->layerPreviewLayout->setAlignment(Qt::AlignTop);

	ui->toolLayout->setAlignment(Qt::AlignTop);
	ui->colorPicker->hide();

	setMinimumSize(740, 600);

	width = qApp->screens()[0]->size().width() / 2;
	height = qApp->screens()[0]->size().height() / 2;
	width = settings.value("window/width", width).toInt();
	height = settings.value("window/height", height).toInt();
	xPos = settings.value("window/xpos", 0).toInt();
	yPos = settings.value("window/ypos", 0).toInt();
	setGeometry(xPos, yPos, width, height);

	ConnectMenuBarActionsToSlots();

	ui->addLayerButton->setDisabled(true);
	ui->deleteLayerButton->setDisabled(true);
	ui->moveLayerUpButton->setDisabled(true);
	ui->moveLayerDownButton->setDisabled(true);

	CreateShortcuts();
}

void MainWindow::ConnectMenuBarActionsToSlots()
{
	connect(ui->actionNew, &QAction::triggered, this, &MainWindow::NewActionClicked);
	connect(ui->actionSave, &QAction::triggered, this, &MainWindow::SaveActionClicked);
	connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::SaveAsActionClicked);
	connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::OpenActionClicked);
}

void MainWindow::ConnectLayerOperationButtonsToSlots()
{
	connect(ui->addLayerButton, &QPushButton::released, this, &MainWindow::CreateLayer);
	connect(ui->deleteLayerButton, &QPushButton::released, this, &MainWindow::ShowLayerDeleteConfirmationDialog);
	connect(ui->moveLayerUpButton, &QPushButton::clicked, this, &MainWindow::MoveLayerUp);
	connect(ui->moveLayerDownButton, &QPushButton::clicked, this, &MainWindow::MoveLayerDown);
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

		graphicsScene->layerSelection.hide();
		if( saveFileDialog.exec() == QFileDialog::Accepted )
		{
			QStringList file = saveFileDialog.selectedFiles();
			QPixmap image(graphicsScene->sceneRect().width(), graphicsScene->sceneRect().height());
			painter.begin(&image);
			graphicsScene->render(&painter);
			painter.end();
			image.save(file[0]);
		}
		graphicsScene->layerSelection.show();
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

	CreateLayer();

	ConnectLayerOperationButtonsToSlots();

	ui->addLayerButton->setDisabled(false);
	ui->deleteLayerButton->setDisabled(false);
	ui->moveLayerUpButton->setDisabled(false);
	ui->moveLayerDownButton->setDisabled(false);
}

void MainWindow::CreateLayer()
{
	auto newLayer = new ImageLayer(graphicsScene->canvas->rect().width(), graphicsScene->canvas->rect().height());
	newLayer->setZValue(layers.size()); //places new layer on top of image
	graphicsScene->AddLayer(newLayer);

	QString layerName = "layer_" + QString::number(layersAddedCount);
	auto layerPreview = new LayerPreview(newLayer, layerName, ui->scrollAreaWidgetContents);
	ui->layerPreviewLayout->addWidget(layerPreview);
	layers.push_back(layerPreview);
	++layersAddedCount;

	connect(layerPreview, &LayerPreview::Selected, this, &MainWindow::ActiveLayerChanged);

	ActiveLayerChanged(layerPreview);
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
	graphicsScene->ChangeActiveLayer(activeLayer->GetLayer());
}

void MainWindow::DeleteActiveLayer()
{
	auto decrementLayerZValue = [](LayerPreview* preview)
	{
		int zValue = preview->GetLayer()->zValue();
		preview->GetLayer()->setZValue(zValue - 1);
	};

	auto iterator = std::find(layers.begin(), layers.end(), activeLayer);
	int index = std::distance(layers.begin(), iterator);
	QLayoutItem* item = ui->layerPreviewLayout->takeAt(index);
	delete item->widget();
	delete item;
	layers.erase(iterator);
	std::for_each(iterator, layers.end(), decrementLayerZValue);

	if( not layers.empty() )
	{
		activeLayer = layers[index != 0 ? index - 1 : index];
		graphicsScene->ChangeActiveLayer(activeLayer->GetLayer());
		activeLayer->Select();
	}
	else
	{
		activeLayer = nullptr;
		graphicsScene->ChangeActiveLayer(nullptr);
	}
}

void MainWindow::MoveLayerUp()
{
	if( not layers.empty() )
	{
		MoveLayer(LayerMoveDirection::Up);
	}
}

void MainWindow::MoveLayerDown()
{
	if( not layers.empty() )
	{
		MoveLayer(LayerMoveDirection::Down);
	}
}

void MainWindow::MoveLayer(LayerMoveDirection direction)
{
	auto layersVectorIterator = std::find(layers.begin(), layers.end(), activeLayer);
	int index = std::distance(layers.begin(), layersVectorIterator);
	LayerPreview* tmpWidget;
	int zValue;

	switch( direction )
	{
		case LayerMoveDirection::Up:
			if( index == 0 )
			{
				return;
			}
			tmpWidget = dynamic_cast<LayerPreview*>(ui->layerPreviewLayout->itemAt(index - 1)->widget());
			zValue = tmpWidget->GetLayer()->zValue();
			tmpWidget->GetLayer()->setZValue(activeLayer->GetLayer()->zValue());
			activeLayer->GetLayer()->setZValue(zValue);
			ui->layerPreviewLayout->removeWidget(tmpWidget);
			ui->layerPreviewLayout->removeWidget(activeLayer);
			ui->layerPreviewLayout->insertWidget(index - 1, activeLayer);
			ui->layerPreviewLayout->insertWidget(index, tmpWidget);
			std::iter_swap(layersVectorIterator, layersVectorIterator - 1);
			break;

		case LayerMoveDirection::Down:
			if( index == layers.size() - 1 )
			{
				return;
			}
			tmpWidget = dynamic_cast<LayerPreview*>(ui->layerPreviewLayout->itemAt(index + 1)->widget());
			zValue = tmpWidget->GetLayer()->zValue();
			tmpWidget->GetLayer()->setZValue(activeLayer->GetLayer()->zValue());
			activeLayer->GetLayer()->setZValue(zValue);
			ui->layerPreviewLayout->removeWidget(tmpWidget);
			ui->layerPreviewLayout->removeWidget(activeLayer);
			ui->layerPreviewLayout->insertWidget(index, tmpWidget);
			ui->layerPreviewLayout->insertWidget(index + 1, activeLayer);
			std::iter_swap(layersVectorIterator, layersVectorIterator + 1);
			break;
	}
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
	QLayoutItem* item;
	if( graphicsScene != nullptr )
	{
		while( ( item = ui->layerPreviewLayout->takeAt(0) ) != nullptr )
		{
			delete item->widget();
			delete item;
		}

		layers.clear();
		graphicsScene->clear();
		graphicsScene = nullptr;
		activeLayer = nullptr;
	}
	layersAddedCount = 0;
}

void MainWindow::CreateScene(int width, int height)
{
	graphicsScene = new GraphicsScene(width, height, ui->colorPicker->GetColor(), this);
	connect(ui->toolBar, &ToolBar::ToolSelected, this, &MainWindow::ToolSelected);
	connect(ctrlV, &QShortcut::activated, graphicsScene, &GraphicsScene::Paste);
	connect(esc, &QShortcut::activated, graphicsScene, &GraphicsScene::CancelSelection);
	connect(hShortcut, &QShortcut::activated, graphicsScene, &GraphicsScene::ToggleLayerSelectionVisibility);
	connect(del, &QShortcut::activated, this, &MainWindow::ShowLayerDeleteConfirmationDialog);

	ui->workSpace->setScene(graphicsScene);
	if( ui->workSpace->width() / width < 1 or ui->workSpace->height() / height < 1 )
	{
		qreal scaleFactorX = static_cast<qreal>(ui->workSpace->width()) / static_cast<qreal>(width);
		qreal scaleFactorY = static_cast<qreal>(ui->workSpace->height()) / static_cast<qreal>(height);
		if( scaleFactorX <= scaleFactorY )
		{
			ui->workSpace->scale(scaleFactorX, scaleFactorX);
		}
		else
		{
			ui->workSpace->scale(scaleFactorY, scaleFactorY);
		}
	}
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
			DeleteActiveLayer();
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

	esc = new QShortcut(this);
	esc->setKey(Qt::Key_Escape);

	hShortcut = new QShortcut(this);
	hShortcut->setKey(Qt::Key_H);
}

void MainWindow::ToolSelected(ActiveTool tool)
{
	if( tool == ActiveTool::Paint or tool == ActiveTool::Pen )
	{
		ui->colorPicker->show();
	}
	else
	{
		ui->colorPicker->hide();
	}
	switch( tool )
	{
		case ActiveTool::Selection:
			ui->activeToolLabel->setText("Narzędzie zaznaczanie");
			break;
		case ActiveTool::Pen:
			ui->activeToolLabel->setText("Pędzel");
			break;
		case ActiveTool::Paint:
			ui->activeToolLabel->setText("Narzędzie wiadro z farbą");
			break;
		case ActiveTool::Move:
			ui->activeToolLabel->setText("Narzędzie przemieszczanie");
			break;
		case ActiveTool::Scale:
			ui->activeToolLabel->setText("Skalowanie");
			break;
		case ActiveTool::Rotation:
			ui->activeToolLabel->setText("Obracanie");
			break;
		case ActiveTool::Text:
			ui->activeToolLabel->setText("Narzędzie tekst");
			break;
	}
	graphicsScene->ChangeActiveTool(tool);
}