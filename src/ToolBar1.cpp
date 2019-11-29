#include "ToolBar1.h"
#include "ui_ToolBar1.h"

ToolBar1::ToolBar1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBar1)
{
    ui->setupUi(this);
}

ToolBar1::~ToolBar1()
{
    delete ui;
}
