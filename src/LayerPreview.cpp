#include "LayerPreview.h"
#include "ui_LayerPreview.h"
#include "ImageLayer.h"

LayerPreview::LayerPreview(ImageLayer* layer, QString& layerIdentifier, QWidget* parent) :
		QWidget(parent),
		selected(false),
		layer(layer),
		ui(new Ui::LayerPreview)
{
	ui->setupUi(this);
	setAutoFillBackground(true);
	ui->layerName->setText(layerIdentifier);
}

LayerPreview::~LayerPreview()
{
	delete layer;
	delete ui;
}

void LayerPreview::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
	if( selected == false )
	{
		emit LayerSelected(this);
	}
}

ImageLayer* LayerPreview::GetLayer()
{
	return layer;
}

void LayerPreview::Unselect()
{
	QPalette palette;
	selected = false;
	palette.setColor(QPalette::Window, Qt::white);
	setPalette(palette);
}
//	graphicsScene->setBackgroundBrush(QColor(123, 123, 123));

void LayerPreview::Select()
{
	QPalette palette;
	selected = true;
	palette.setColor(QPalette::Window, QColor(140, 204, 245));
	setPalette(palette);
}

QString LayerPreview::GetLayerName()
{
	return ui->layerName->text();
}