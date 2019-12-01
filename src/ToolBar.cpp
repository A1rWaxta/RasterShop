#include "ToolBar.h"
#include "ui_ToolBar.h"

ToolBar::ToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBar)
{
    ui->setupUi(this);
}

ToolBar::~ToolBar()
{
    delete ui;
}
