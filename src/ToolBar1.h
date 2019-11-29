#ifndef TOOLBAR1_H
#define TOOLBAR1_H

#include <QWidget>

namespace Ui {
class ToolBar1;
}

class ToolBar1 : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBar1(QWidget *parent = nullptr);
    ~ToolBar1();

private:
    Ui::ToolBar1 *ui;
};

#endif // TOOLBAR1_H
