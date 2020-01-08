#include <QtWidgets/QColorDialog>
#include "ColorPicker.h"
#include "ui_ColorPicker.h"

ColorPicker::ColorPicker(QWidget *parent) :
    QWidget(parent),
    selectedColor(QColor(Qt::white)),
    ui(new Ui::ColorPicker)
{
    ui->setupUi(this);
	QPalette palette;
	palette.setColor(QPalette::Window, selectedColor);
	ui->colorPreview->setAutoFillBackground(true);

	connect(ui->colorPickerButton, &QPushButton::released, this, &ColorPicker::OpenColorPicker);
}

ColorPicker::~ColorPicker()
{
    delete ui;
}

void ColorPicker::OpenColorPicker()
{
	selectedColor = QColorDialog::getColor();
	QPalette palette;
	palette.setColor(QPalette::Window, selectedColor);
	ui->colorPreview->setPalette(palette);
}

QColor& ColorPicker::GetColor()
{
	return selectedColor;
}