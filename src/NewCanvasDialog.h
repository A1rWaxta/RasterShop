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
	[[nodiscard]] int GetCanvasWidth() const;
	[[nodiscard]] int GetCanvasHeight() const;
	[[nodiscard]] QColor & GetCanvasColor();

private slots:
	void OpenColorPicker();
	void AcceptDialog();

private:
    QColor backgroundColor;
	int canvasWidth;
	int canvasHeight;
	Ui::NewCanvasDialog *ui;
};