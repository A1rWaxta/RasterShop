#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QWidget>

namespace Ui {
class ColorPicker;
}

class ColorPicker : public QWidget
{
    Q_OBJECT

public:
    explicit ColorPicker(QWidget *parent = nullptr);
    ~ColorPicker();
    QColor& GetColor();

private slots:
	void OpenColorPicker();

private:
	QColor selectedColor;
	Ui::ColorPicker *ui;
};

#endif // COLORPICKER_H
