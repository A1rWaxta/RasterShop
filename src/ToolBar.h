#ifndef TOOLBAR1_H
#define TOOLBAR1_H

#include <QWidget>

namespace Ui {
class ToolBar;
}

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBar(QWidget *parent = nullptr);
    ~ToolBar();

private:
    Ui::ToolBar *ui;
};

#endif // TOOLBAR1_H
