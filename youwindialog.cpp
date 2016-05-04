#include "youwindialog.h"
#include "ui_youwindialog.h"

YouWinDialog::YouWinDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YouWinDialog)
{
    ui->setupUi(this);
}

YouWinDialog::~YouWinDialog()
{
    delete ui;
}

void YouWinDialog::on_joinButton_clicked()
{
    this->close();
}
