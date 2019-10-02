#ifndef MAINWINDOWX_H
#define MAINWINDOWX_H

#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindowX : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowX(QWidget *parent = nullptr);
    
    ~MainWindowX();

    void Show();

private:
    Ui::MainWindow *ui;
    
    void closeEvent(QCloseEvent * closeEvent) override;

    void resizeEvent(QResizeEvent * resizeEvent) override;

    void moveEvent(QMoveEvent * moveEvent) override;

    QMenuBar * menuBar;
};

#endif // MAINWINDOWX_H
