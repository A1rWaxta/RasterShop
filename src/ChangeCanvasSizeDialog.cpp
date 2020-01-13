#include "ChangeCanvasSizeDialog.h"
#include "ui_ChangeCanvasSizeDialog.h"

ChangeCanvasSizeDialog::ChangeCanvasSizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeCanvasSizeDialog)
{
    ui->setupUi(this);
    connect(ui->acceptButton, &QPushButton::released, this, &ChangeCanvasSizeDialog::AcceptDialog);
}

ChangeCanvasSizeDialog::~ChangeCanvasSizeDialog()
{
    delete ui;
}

void ChangeCanvasSizeDialog::AcceptDialog()
{
	newWidth = ui->widthSpinBox->value();
	newHeight = ui->heightSpinBox->value();

	emit accept();
}

QSizeF ChangeCanvasSizeDialog::GetSize()
{
	return QSizeF(newWidth, newHeight);
}

void ChangeCanvasSizeDialog::SetSize(QSize size)
{
	ui->widthSpinBox->setValue(size.width());
	ui->heightSpinBox->setValue(size.height());
}