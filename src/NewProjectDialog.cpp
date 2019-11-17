#include "NewProjectDialog.h"
#include "ui_NewProjectDialog.h"

NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog)
{
    ui->setupUi(this);
	acceptButton = findChild<QPushButton*>("pushButton");
    textField = findChild<QTextEdit*>("textEdit");

    connect(acceptButton, &QPushButton::clicked, this, &NewProjectDialog::AcceptButtonClicked);
}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}

void NewProjectDialog::AcceptButtonClicked()
{
	done(13);
	emit DialogAccepted(textField->toPlainText());
}

void NewProjectDialog::done(int r)
{
#ifdef DEBUG
	qDebug("closing windwow");
#endif
	QDialog::done(r);
}