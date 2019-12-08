#include "LayerPreview.h"
#include "ui_LayerPreview.h"
#include "ImageLayer.h"

LayerPreview::LayerPreview(ImageLayer* layer, QWidget* parent) :
		QWidget(parent),
		selected(false),
		layer(layer),
		ui(new Ui::LayerPreview)
{
	ui->setupUi(this);
	setAutoFillBackground(true);

	ui->layerName->setText(layer->GetIdentifier());
}

LayerPreview::~LayerPreview()
{
	delete layer;
	delete ui;
}

void LayerPreview::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
	emit LayerSelected(this);
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

void LayerPreview::Select()
{
	QPalette palette;
	selected = true;
	palette.setColor(QPalette::Window, QColor(140, 204, 245));
	setPalette(palette);
}