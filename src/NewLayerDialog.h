#pragma once

#include <QDialog>

namespace Ui {
class NewLayerDialog;
}

class NewLayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewLayerDialog(QSize currentCanvasSize, QSize currentSelectionSize, QWidget* parent);
	QSize GetSize();
	QString GetLayerName();
    ~NewLayerDialog() override;

private slots:

	void SetSize(int i);
private:
	QSize newLayerSize;
	QString newLayerName;
	const QSize currentCanvasSize;
	const QSize currentSelectionSize;
	QSize clipboradImageSize;
	Ui::NewLayerDialog *ui;
	void Accept();
};