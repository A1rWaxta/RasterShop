#ifndef MAINWINDOWX_H
#define MAINWINDOWX_H

#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    
    ~MainWindow();

    void Show();

private slots:
	void CreateNewProject();

	void NewCanvas(const QString & string);

private:
    Ui::MainWindow *ui;
    
    void closeEvent(QCloseEvent * closeEvent) override;

    void resizeEvent(QResizeEvent * resizeEvent) override;

    void moveEvent(QMoveEvent * moveEvent) override;

    QMenuBar * menuBar;

    QLabel * label;
};

#endif // MAINWINDOWX_H
