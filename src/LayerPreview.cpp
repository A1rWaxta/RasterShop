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
	connect(ui->visiblityCheckBox, &QCheckBox::stateChanged, this, &LayerPreview::ToggleVisibility);
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
		emit Selected(this);
	}
}

ImageLayer* LayerPreview::GetLayer()
{
	return layer;
}

void LayerPreview::Unselect()
{
	QPalette palette;
	palette.setColor(QPalette::Window, Qt::white);
	selected = false;
	setPalette(palette);

	layer->setSelected(false);
}

void LayerPreview::Select()
{
	QPalette palette;
	palette.setColor(QPalette::Window, QColor(140, 204, 245));
	selected = true;
	setPalette(palette);

	layer->setSelected(true);
}

QString LayerPreview::GetLayerName()
{
	return ui->layerName->text();
}

void LayerPreview::ToggleVisibility()
{
	if(layer->isVisible())
	{
		layer->hide();
	}
	else
	{
		layer->show();
	}
}