#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->errorLabel->hide();
    resetWindow();
}


LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_joinButton_clicked()
{
    //Check login info with db
    //ui->usernameBox->setText("testUser");
    //ui->passwordBox->setText("campain");
    emit(loginButtonClicked(ui->usernameBox->text(), ui->passwordBox->text()));

//this is for locoal access when the server is down.... Also need to comment all client / server connections in main.cpp
//    emit switchToWindow(0);
//    this->close();
//    resetWindow();
}

void LoginDialog::on_cancelButton_clicked()
{
    this->close();
    resetWindow();
}

void LoginDialog::receiveLoginInfo(QStringList loginInfo)
{
    if(loginInfo.size() > 1)
    {
        emit sendGameInfo(loginInfo);
        emit switchToWindow(0);
        this->close();
        resetWindow();
    }
    else
    {
        ui->errorLabel->show();
        ui->errorLabel->setText(loginInfo[0]);
    }
}

void LoginDialog::resetWindow()
{
    this->move(250,150);
    ui->usernameBox->setText("");
    ui->passwordBox->setText("");
}
