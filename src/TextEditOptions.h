#pragma once

#include <QWidget>

namespace Ui {
class TextEditOptions;
}

class TextEditOptions : public QWidget
{
    Q_OBJECT

public:
    explicit TextEditOptions(QWidget *parent = nullptr);
    ~TextEditOptions();
	QFont& GetFont();
	int& GetSize();

public slots:
	void UpdateCurrentFont(const QFont& font);
	void UpdateSize(int i);

private:
	QFont currentFont;
	int currentFontSize;
    Ui::TextEditOptions *ui;
};