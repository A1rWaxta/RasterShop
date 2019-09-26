#ifndef MAINWINDOWX_H
#define MAINWINDOWX_H

#include <QtWidgets>

namespace Ui {
class MainWindowX;
}

class MainWindowX : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowX(QWidget *parent = nullptr);
    
    ~MainWindowX();

    void Show();

private:
    Ui::MainWindowX *ui;
    
    void closeEvent(QCloseEvent * closeEvent) override;

    void resizeEvent(QResizeEvent * resizeEvent) override;

    QMenuBar * menuBar;
};

#endif // MAINWINDOWX_H
