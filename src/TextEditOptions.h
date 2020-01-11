#ifndef TEXTEDITOPTIONS_H
#define TEXTEDITOPTIONS_H

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

private:
    Ui::TextEditOptions *ui;
};

#endif // TEXTEDITOPTIONS_H
