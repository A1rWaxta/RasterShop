#pragma once

#include <QDialog>

namespace Ui {
class ChangeCanvasSizeDialog;
}

class ChangeCanvasSizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeCanvasSizeDialog(QWidget *parent = nullptr);
    ~ChangeCanvasSizeDialog();
    QSizeF GetSize();
    void SetSize(QSize size);

private slots:
	void AcceptDialog();

private:
	int newWidth;
	int newHeight;
    Ui::ChangeCanvasSizeDialog *ui;
};