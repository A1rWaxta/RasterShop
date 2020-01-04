#include "LayerPreview.h"
#include "ui_LayerPreview.h"
#include "ImageLayer.h"

LayerPreview::LayerPreview(QWidget* parent) :
		QWidget(parent),
		selected(false),
		ui(new Ui::LayerPreview)
{
	ui->setupUi(this);
	setAutoFillBackground(true);
}

LayerPreview::~LayerPreview()
{
	delete ui;
}

void LayerPreview::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
	if( selected == false )
	{
		emit Selected(this);
	}
}

void LayerPreview::Unselect()
{
	QPalette palette;
	palette.setColor(QPalette::Window, Qt::white);
	selected = false;
	setPalette(palette);
}

void LayerPreview::Select()
{
	QPalette palette;
	palette.setColor(QPalette::Window, QColor(140, 204, 245));
	selected = true;
	setPalette(palette);
}

QString LayerPreview::GetLayerName()
{
	return ui->layerName->text();
}

void LayerPreview::SetLayerName(QString& name)
{
	ui->layerName->setText(name);
}