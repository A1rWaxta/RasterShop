#include <QtWidgets/QColorDialog>
#include "NewCanvasDialog.h"
#include "ui_NewCanvasDialog.h"
#include <QDebug>
#include <QPainter>

NewCanvasDialog::NewCanvasDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCanvasDialog),
    backgroundColor(Qt::white)
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
	emit DialogAccepted(
			ui->widthSpinBox->text().toInt(),
			ui->heightSpinBox->text().toInt(),
			backgroundColor
	);
	emit accept();
}