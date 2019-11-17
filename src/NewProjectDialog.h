#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QtWidgets>

namespace Ui {
class NewProjectDialog;
}

class NewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewProjectDialog(QWidget *parent = nullptr);

    ~NewProjectDialog();

private slots:
	void AcceptButtonClicked();

signals:
	void DialogAccepted(QString string);

private:
    Ui::NewProjectDialog *ui;

	QPushButton *acceptButton;

	QTextEdit *textField;

	void done(int r) override;
};

#endif // NEWPROJECTDIALOG_H
