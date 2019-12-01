#pragma once

#include <QDialog>

namespace Ui {
class NewCanvasDialog;
}

class NewCanvasDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewCanvasDialog(QWidget *parent = nullptr);
    ~NewCanvasDialog() override;

private slots:
	void OpenColorPicker();
	void AcceptDialog();

signals:
	void DialogAccepted(int width, int height, QColor color);

private:
    QColor backgroundColor;

	Ui::NewCanvasDialog *ui;
};