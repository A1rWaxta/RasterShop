#include "MainWindow.h"
#include "ui_MainWindowX.h"
#include "NewCanvasDialog.h"
#include "LayerPreview.h"
#include "ChangeCanvasSizeDialog.h"
#include "NewLayerDialog.h"
#include <QtSvg/QGraphicsSvgItem>
#include <opencv2/core/mat.hpp>

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
	ui->textEditOptions->hide();

	ui->tabWidget->setDisabled(true);
	ui->menuEdit->setDisabled(true);
	ui->menuFiltry->setDisabled(true);
	ui->menuObraz->setDisabled(true);

	setMinimumSize(740, 600);

	width = qApp->screens()[0]->size().width() / 2;
	height = qApp->screens()[0]->size().height() / 2;
	width = settings.value("window/width", width).toInt();
	height = settings.value("window/height", height).toInt();
	xPos = settings.value("window/xpos", 0).toInt();
	yPos = settings.value("window/ypos", 0).toInt();
	setGeometry(xPos, yPos, width, height);

	ConnectMenuBarActionsToSlots();
	CreateShortcuts();
	ConnectLayerOperationButtonsToSlots();

	QPixmap pixmap;

	pixmap.load("res/plus.svg");
	QIcon addLayerIcon(pixmap);
	ui->addLayerButton->setIcon(addLayerIcon);
	ui->addLayerButton->setIconSize(QSize(37, 37));

	pixmap.load("res/trash.svg");
	QIcon deleteLayerIcon(pixmap);
	ui->deleteLayerButton->setIcon(deleteLayerIcon);
	ui->deleteLayerButton->setIconSize(QSize(37, 37));

	pixmap.load("res/arrowUp.svg");
	QIcon moveLayerUpIcon(pixmap);
	ui->moveLayerUpButton->setIcon(moveLayerUpIcon);
	ui->moveLayerUpButton->setIconSize(QSize(37, 37));

	pixmap.load("res/arrowDown.svg");
	QIcon moveLayerDownIcon(pixmap);
	ui->moveLayerDownButton->setIcon(moveLayerDownIcon);
	ui->moveLayerDownButton->setIconSize(QSize(37, 37));
}

void MainWindow::ConnectMenuBarActionsToSlots()
{
	connect(ui->actionNew, &QAction::triggered, this, &MainWindow::NewActionClicked);
	connect(ui->actionSave, &QAction::triggered, this, &MainWindow::SaveActionClicked);
	connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::SaveAs);
	connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::OpenActionClicked);

	connect(ui->actionChangeSize, &QAction::triggered, this, &MainWindow::ChangeCanvasSize);
	connect(ui->actionRotate90DegreesRight, &QAction::triggered, this, &MainWindow::Rotate90DegreesRight);
	connect(ui->actionRotate90DegreesLeft, &QAction::triggered, this, &MainWindow::Rotate90DegreesLeft);
	connect(ui->actionRotate180Degrees, &QAction::triggered, this, &MainWindow::Rotate180Degrees);

	connect(ui->grayScaleAction, &QAction::triggered, this, &MainWindow::GrayScaleLayer);

	connect(ui->actionAddImage, &QAction::triggered, this, &MainWindow::AddImage);
	connect(ui->actionUnselect, &QAction::triggered, this, &MainWindow::CancelSelection);
}

void MainWindow::ConnectLayerOperationButtonsToSlots()
{
	connect(ui->addLayerButton, &QPushButton::released, this, &MainWindow::ShowLayerCreationDialog);
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

void MainWindow::SaveAs()
{
	QPainter painter;
	painter.setRenderHint(QPainter::Antialiasing);
	if( graphicsScene != nullptr )
	{
		QFileDialog saveFileDialog(this);
		saveFileDialog.setAcceptMode(QFileDialog::AcceptSave);
		saveFileDialog.setNameFilter("*.png *.bmp *.jpg *.jpeg");

		graphicsScene->HideTools();
		if( saveFileDialog.exec() == QFileDialog::Accepted )
		{
			QStringList file = saveFileDialog.selectedFiles();
			QPixmap image(graphicsScene->canvas->rect().width(), graphicsScene->canvas->rect().height());
			painter.begin(&image);
			graphicsScene->render(&painter, graphicsScene->canvas->rect(), graphicsScene->canvas->rect());
			painter.end();
			image.save(file[0]);
		}
		graphicsScene->ShowTools();
	}
}

void MainWindow::SaveActionClicked()
{

}

void MainWindow::OpenActionClicked()
{
	QFileDialog fileDialog(this);
	QMessageBox::StandardButton svgFileOpenedReply;

	fileDialog.resize(320, 100);
	fileDialog.setNameFilter(tr("Images (*.png *.bmp *.jpg *.jpeg *.svg)"));
	fileDialog.setFileMode(QFileDialog::ExistingFile);

	QStringList fileNames;
	if( fileDialog.exec() == QFileDialog::Accepted )
	{
		fileNames = fileDialog.selectedFiles();

		QImage image(fileNames[0]);

		InitializeNewProject(image.width(), image.height());

		QFileInfo fileInfo(fileNames[0]);
		if( fileInfo.suffix() == "svg" )
		{
			svgFileOpenedReply = QMessageBox::question(this, tr("Format svg"),
			                                           tr("Wybrano plik w formacie svg. Czy chcesz rasteryzować?"));
			if( svgFileOpenedReply == QMessageBox::No )
			{
				auto vectorGraphicsImage = new QGraphicsSvgItem(fileNames[0]);
				graphicsScene->AddItemOnActiveLayer(vectorGraphicsImage);
			}
			else
			{
				auto graphicsImage = new QGraphicsPixmapItem(QPixmap::fromImage(image));
				graphicsScene->AddItemOnActiveLayer(graphicsImage);
			}
		}
		else
		{
			auto graphicsImage = new QGraphicsPixmapItem(QPixmap::fromImage(image));
			graphicsScene->AddItemOnActiveLayer(graphicsImage);
		}
	}
}

void MainWindow::InitializeNewProject(int width, int height)
{
	ClearScene();

	CreateScene(width, height);

	CreateLayer(width, height, tr("tło"));

	ui->tabWidget->setEnabled(true);
	ui->menuEdit->setEnabled(true);
	ui->menuFiltry->setEnabled(true);
	ui->menuObraz->setEnabled(true);
}

void MainWindow::CreateLayer(int width, int height, QString layerName)
{
	auto newLayer = new ImageLayer(width, height);
	newLayer->setZValue(layers.size()); //places new layer on top of image
	graphicsScene->AddLayer(newLayer);

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
		backgroundRectangle->setPen(Qt::NoPen);
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
		delete graphicsScene;
		graphicsScene = nullptr;
		activeLayer = nullptr;
	}
	layersAddedCount = 0;
}

void MainWindow::CreateScene(int width, int height)
{

	graphicsScene = new GraphicsScene(width, height, ui->colorPicker->GetColor(), ui->textEditOptions->GetFont(),
	                                  ui->textEditOptions->GetSize(),
	                                  this);
	connect(ui->toolBar, &ToolBar::ToolSelected, this, &MainWindow::ToolSelected);
	connect(ctrlV, &QShortcut::activated, graphicsScene, &GraphicsScene::Paste);
	connect(esc, &QShortcut::activated, graphicsScene, &GraphicsScene::CancelSelection);
	connect(ctrlH, &QShortcut::activated, graphicsScene, &GraphicsScene::ToggleLayerSelectionVisibility);
	connect(del, &QShortcut::activated, this, &MainWindow::ShowLayerDeleteConfirmationDialog);
	connect(ctrlS, &QShortcut::activated, this, &MainWindow::SaveAs);
	connect(ctrlN, &QShortcut::activated, this, &MainWindow::ShowLayerCreationDialog);
	connect(ui->actionPaste, &QAction::triggered, graphicsScene, &GraphicsScene::Paste);

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

	ctrlH = new QShortcut(this);
	ctrlH->setKey(Qt::CTRL + Qt::Key_H);

	ctrlS = new QShortcut(this);
	ctrlS->setKey(Qt::CTRL + Qt::Key_S);

	ctrlN = new QShortcut(this);
	ctrlN->setKey(Qt::CTRL + Qt::Key_N);
}

void MainWindow::ToolSelected(ActiveTool tool)
{
	if( tool == ActiveTool::Paint or tool == ActiveTool::Pen or tool == ActiveTool::Text )
	{
		ui->colorPicker->show();

	}
	else
	{
		ui->colorPicker->hide();
	}
	if( tool == ActiveTool::Text )
	{
		ui->textEditOptions->show();
	}
	else
	{
		ui->textEditOptions->hide();
	}
	switch( tool )
	{
		case ActiveTool::Selection:
			ui->activeToolLabel->setText(tr("Narzędzie zaznaczanie"));
			break;
		case ActiveTool::Pen:
			ui->activeToolLabel->setText(tr("Pędzel"));
			break;
		case ActiveTool::Paint:
			ui->activeToolLabel->setText(tr("Narzędzie wiadro z farbą"));
			break;
		case ActiveTool::Move:
			ui->activeToolLabel->setText(tr("Narzędzie przemieszczanie"));
			break;
		case ActiveTool::Scale:
			ui->activeToolLabel->setText(tr("Skalowanie"));
			break;
		case ActiveTool::Rotation:
			ui->activeToolLabel->setText(tr("Obracanie"));
			break;
		case ActiveTool::Text:
			ui->activeToolLabel->setText(tr("Narzędzie tekst"));
			break;
		case ActiveTool::Polygon:
			ui->activeToolLabel->setText(tr("Swobodny kształt"));
			break;
	}
	graphicsScene->ChangeActiveTool(tool);
}

void MainWindow::ChangeCanvasSize()
{
	int width;
	int height;
	ChangeCanvasSizeDialog canvasSizeDialog;
	canvasSizeDialog.SetSize(graphicsScene->canvas->rect().size().toSize());

	if( canvasSizeDialog.exec() == QDialog::Accepted )
	{
		QSizeF newSize(canvasSizeDialog.GetSize());
		QRectF newRect(graphicsScene->canvas->pos(), newSize);
		graphicsScene->canvas->setRect(newRect);
		ui->workSpace->setSceneRect(graphicsScene->itemsBoundingRect());
	}
}

void MainWindow::Rotate90DegreesLeft()
{
	ui->workSpace->rotate(-90);
}

void MainWindow::Rotate90DegreesRight()
{
	ui->workSpace->rotate(90);
}

void MainWindow::Rotate180Degrees()
{
	ui->workSpace->rotate(180);
}

void MainWindow::ShowLayerCreationDialog()
{
	const auto canvasSize = graphicsScene->canvas->rect().size().toSize();
	auto selectionSize = graphicsScene->rectangleSelectionTool.rect().size().toSize();
	selectionSize.setHeight(-selectionSize.height());
	NewLayerDialog newLayerDialog(canvasSize, selectionSize, nullptr);

	bool isDuplicate = false;

	if( newLayerDialog.exec() == QDialog::Accepted )
	{
		QSize newLayerSize = newLayerDialog.GetSize();
		QString newLayerName = newLayerDialog.GetLayerName();
		for( auto layerPreview : layers )
		{
			if( layerPreview->GetLayerName() == newLayerName )
			{
				isDuplicate = true;
				break;
			}
		}
		if( isDuplicate )
		{
			QMessageBox::critical(nullptr, tr("Błąd"), tr("Warstwa o podanej nazwie już istnieje!"));
		}
		else
		{
			CreateLayer(newLayerSize.width(), newLayerSize.height(), newLayerName);
		}
	}
}

void MainWindow::GrayScaleLayer()
{
	if( graphicsScene != nullptr )
	{
		graphicsScene->HideTools();
		for( auto layer : layers )
		{
			layer->GetLayer()->hide();
		}
		QImage image = graphicsScene->activeLayer->ToImage();
		for( auto layer : layers )
		{
			layer->GetLayer()->show();
		}

		for( int ii = 0; ii < image.height(); ii++ )
		{
			uchar* scan = image.scanLine(ii);
			int depth = 4;
			for( int jj = 0; jj < image.width(); jj++ )
			{

				QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + jj * depth);
				int gray = qGray(*rgbpixel);
				*rgbpixel = QColor(gray, gray, gray).rgba();
			}
		}

		auto newImageLayer = new ImageLayer(image.width(), image.height());
		newImageLayer->setRect(activeLayer->GetLayer()->rect());
		auto rasterizedOldLayer = new QGraphicsPixmapItem(QPixmap::fromImage(image));
		graphicsScene->AddItemOnActiveLayer(rasterizedOldLayer);

		graphicsScene->ShowTools();
//		QDialog dialog;
//		QLabel label;
//		label.setPixmap(QPixmap::fromImage(image));
//		label.setParent(&dialog);
//		dialog.show();
//		dialog.exec();
	}
}

void MainWindow::AddImage()
{
	QFileDialog fileDialog(this);
	QMessageBox::StandardButton svgFileOpenedReply;

	fileDialog.resize(320, 100);
	fileDialog.setNameFilter(tr("Images (*.png *.bmp *.jpg *.jpeg *.svg)"));
	fileDialog.setFileMode(QFileDialog::ExistingFile);

	QStringList fileNames;
	if( fileDialog.exec() == QFileDialog::Accepted )
	{
		fileNames = fileDialog.selectedFiles();

		QImage image(fileNames[0]);

		CreateLayer(image.width(), image.height(), "warstwa_" + QString::number(layers.size()));

		QFileInfo fileInfo(fileNames[0]);
		if( fileInfo.suffix() == "svg" )
		{
			svgFileOpenedReply = QMessageBox::question(this, tr("Format svg"),
			                                           tr("Wybrano plik w formacie svg. Czy chcesz rasteryzować?"));
			if( svgFileOpenedReply == QMessageBox::No )
			{
				auto vectorGraphicsImage = new QGraphicsSvgItem(fileNames[0]);
				graphicsScene->AddItemOnActiveLayer(vectorGraphicsImage);
			}
			else
			{
				auto graphicsImage = new QGraphicsPixmapItem(QPixmap::fromImage(image));
				graphicsScene->AddItemOnActiveLayer(graphicsImage);
			}
		}
		else
		{
			auto graphicsImage = new QGraphicsPixmapItem(QPixmap::fromImage(image));
			graphicsScene->AddItemOnActiveLayer(graphicsImage);
		}
	}
}

void MainWindow::CancelSelection()
{
	graphicsScene->CancelSelection();
}