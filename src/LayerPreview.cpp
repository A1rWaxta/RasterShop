#include "LayerPreview.h"
#include "ui_LayerPreview.h"

LayerPreview::LayerPreview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerPreview),
    selected(false)
{
    ui->setupUi(this);
    setAutoFillBackground(true);
}

LayerPreview::~LayerPreview()
{
    delete ui;
}

void LayerPreview::SetLayerName(QString& layerName)
{
	ui->layerName->setText(layerName);
}

void LayerPreview::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
	if( selected == false )
	{
		selected = true;
		QPalette palette;
		palette.setColor(QPalette::Window, Qt::blue);
		setPalette(palette);
	}
}