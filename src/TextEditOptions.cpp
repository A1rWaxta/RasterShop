#include "TextEditOptions.h"
#include "ui_TextEditOptions.h"
#include <QDebug>

TextEditOptions::TextEditOptions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextEditOptions)
{
    ui->setupUi(this);

    connect(ui->fontComboBox, &QFontComboBox::currentFontChanged, this, &TextEditOptions::UpdateCurrentFont);
	connect(ui->fontSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(UpdateSize(int)));
}

TextEditOptions::~TextEditOptions()
{
    delete ui;
}

QFont& TextEditOptions::GetFont()
{
	return currentFont;
}

int& TextEditOptions::GetSize()
{
	return currentFontSize;
}

void TextEditOptions::UpdateCurrentFont(const QFont& font)
{
	qDebug() << "TextOptionsdebug font" << font.family();
	currentFont = font;
}

void TextEditOptions::UpdateSize(int i)
{
	qDebug() << "TextOptionsdebug size" << i;
	currentFontSize = i;
}