#include "signupdialog.h"
#include "ui_signupdialog.h"

SignUpDialog::SignUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    ui->setupUi(this);
    ui->errorLabel->hide();
    resetWindow();
}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}

void SignUpDialog::on_cancelButton_clicked()
{
    this->close();
    resetWindow();
}

void SignUpDialog::on_joinButton_clicked()
{
    //make sure username & password boxes are not empty.
    if(ui->usernameBox->text().size() < 6){
        ui->errorLabel->setText("Please enter valid username.\n Must be at least 6 characters.");
        ui->errorLabel->show();
    } else if (ui->passwordBox->text().size() < 6) {
        ui->errorLabel->setText("Please enter valid password.\n Must be at least 6 characters.");
        ui->errorLabel->show();
    } else if(ui->groupIdBox->text().size() < 6){
        ui->errorLabel->setText("Please enter valid group Id.\n Must be at least 6 characters.");
        ui->errorLabel->show();
    } else if (ui->groupPasswordBox->text().size() < 6) {
        ui->errorLabel->setText("Please enter valid group password.\n Must be at least 6 characters.");
        ui->errorLabel->show();
    } else if (!(ui->createAdminRadio->isChecked() || ui->createUserRadio->isChecked())){
        ui->errorLabel->setText("Please select an account type.\n");
        ui->errorLabel->show();
    }
    else {
        //double check username with database.      TODO

        bool isAdmin;
        if(ui->createAdminRadio->isChecked()){
            isAdmin = true;
        } else if(ui->createAdminRadio->isChecked()) {
            isAdmin = false;
        }

        emit(joinButtonClicked(ui->usernameBox->text(), ui->passwordBox->text(), ui->groupIdBox->text(), ui->groupPasswordBox->text(), isAdmin ));
        //if username already exists, update errorLabel and tell user to try again.     TODO

    }
}

void SignUpDialog::resetWindow()
{
    this->move(250,150);
    ui->passwordBox->setText("");
    ui->groupPasswordBox->setText("");
    ui->groupIdBox->setText("");
    ui->usernameBox->setText("");
}

void SignUpDialog::checkSignupErrors(QString message)
{
    if (message.size() > 0)
    {
        ui->errorLabel->setText(message);
        ui->errorLabel->show();
    }
    else
    {

        //if valid, send signal and log in user (switch to gameMenu view)          TODO
        //close dialog window. return to main menu.     TODO
        this->close();
        resetWindow();
    }
}
