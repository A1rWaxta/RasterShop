#include <QtWidgets/QColorDialog>
#include "NewCanvasDialog.h"
#include "ui_NewCanvasDialog.h"
#include <QDebug>
#include <QPainter>

NewCanvasDialog::NewCanvasDialog(QWidget *parent) :
    QDialog(parent),
    backgroundColor(Qt::transparent),
	ui(new Ui::NewCanvasDialog)
{
	QPalette palette;

    ui->setupUi(this);

    connect(ui->setColorButton, &QPushButton::released, this, &NewCanvasDialog::OpenColorPicker);
    connect(ui->okButton, &QPushButton::released, this, &NewCanvasDialog::AcceptDialog);
    connect(ui->cancelButton, &QPushButton::released, this, &NewCanvasDialog::reject);
}

NewCanvasDialog::~NewCanvasDialog()
{
    delete ui;
}

void NewCanvasDialog::OpenColorPicker()
{
	backgroundColor = QColorDialog::getColor();
	QPalette palette;
	palette.setColor(QPalette::Window, backgroundColor);

	ui->colorPreview->setAutoFillBackground(true);
	ui->colorPreview->setPalette(palette);
}

void NewCanvasDialog::AcceptDialog()
{
	canvasWidth = ui->widthSpinBox->text().toInt();
	canvasHeight = ui->heightSpinBox->text().toInt();
	emit accept();
}

int NewCanvasDialog::GetCanvasWidth() const
{
	return canvasWidth;
}

int NewCanvasDialog::GetCanvasHeight() const
{
	return canvasHeight;
}

QColor &NewCanvasDialog::GetCanvasColor()
{
	return backgroundColor;
}