#include <QtGui/QClipboard>
#include "NewLayerDialog.h"
#include "ui_NewLayerDialog.h"
#include <QDebug>

NewLayerDialog::NewLayerDialog(QSize currentCanvasSize, QWidget* parent) :
		QDialog(parent),
		currentCanvasSize(currentCanvasSize),
		ui(new Ui::NewLayerDialog)
{
	ui->setupUi(this);
	QClipboard* clipboard = QGuiApplication::clipboard();
	clipboradImageSize = clipboard->pixmap().size();
	if( clipboradImageSize == QSize(0, 0) )
	{
    	ui->sizeComboBox->removeItem(2);
	}

	connect(ui->acceptButton, &QPushButton::released, this, &NewLayerDialog::Accept);
	connect(ui->cancelButton, &QPushButton::released, this, &NewLayerDialog::reject);
	connect(ui->sizeComboBox, SIGNAL(activated(int)), this, SLOT(SetSize(int)));
}

NewLayerDialog::~NewLayerDialog()
{
	delete ui;
}

QSize NewLayerDialog::GetSize()
{
	return newLayerSize;
}

void NewLayerDialog::Accept()
{
	newLayerSize.setWidth(ui->widthSpinBox->value());
	newLayerSize.setHeight(ui->heightSpinBox->value());
	newLayerName = ui->layerNameLineEdit->text();

	emit accept();
}

void NewLayerDialog::SetSize(int i)
{
	switch(i)
	{
		case 0:
		{
			break;
		}
		case 1:
		{
			ui->widthSpinBox->setValue(currentCanvasSize.width());
			ui->heightSpinBox->setValue(currentCanvasSize.height());
			break;
		}
		case 2:
		{
			ui->widthSpinBox->setValue(clipboradImageSize.width());
			ui->heightSpinBox->setValue(clipboradImageSize.height());
			break;
		}
		default:
		{
			break;
		}
	}
}

QString NewLayerDialog::GetLayerName()
{
	return newLayerName;
}