#include "TextEditOptions.h"
#include "ui_TextEditOptions.h"

TextEditOptions::TextEditOptions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextEditOptions)
{
    ui->setupUi(this);
}

TextEditOptions::~TextEditOptions()
{
    delete ui;
}
