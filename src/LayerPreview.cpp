#include "LayerPreview.h"
#include "ui_LayerPreview.h"
#include "ImageLayer.h"
#include <QDebug>

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
	connect(ui->opacitySpinBox, SIGNAL(valueChanged(int)), this, SLOT(SetOpacity(int)));
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

void LayerPreview::SetOpacity(int value)
{
	double i = static_cast<double>(value) / 100;
	layer->setOpacity(i);
}

void LayerPreview::SetLayer(ImageLayer *layer)
{
	this->layer = layer;
}