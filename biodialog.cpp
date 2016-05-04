#include "biodialog.h"
#include "ui_biodialog.h"

BioDialog::BioDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BioDialog)
{
    ui->setupUi(this);
    this->move(250,150);
}

BioDialog::~BioDialog()
{
    delete ui;
}

void BioDialog::on_doneButton_clicked()
{
    //close the dialog.
    this->close();
}

void BioDialog::updateInfo(QString _name, QString _age, QString _from, QString _party, QString _job, QString _bio){
    ui->nameLabel->setText("Name: " + _name);
    ui->ageLabel->setText("Age: " + _age);
    ui->fromLabel->setText("From: " + _from);
    ui->partyLabel->setText("Party: " + _party);
    ui->jobLabel->setText("Occupation: " + _job);
    ui->bioLabel->setWordWrap(true);
    ui->bioLabel->setText(_bio);
    if(_name == "Donald John Trump, Sr"){
        ui->label->setStyleSheet(
              "border-image: url(:/head/Resources/headshot_dc-celebrity-portrait-photographers.jpg)");
    } else if(_name == "Hillary Rodham Clinton") {
        ui->label->setStyleSheet(
              "border-image: url(:/head/Resources/Hillary-Clinton.jpg)");
    } else if(_name == "Bernard Sanders") {
        ui->label->setStyleSheet(
              "border-image: url(:/head/Resources/Sanders_SQ.png)");
    }else if(_name == "Rafael Edward Cruz") {
        ui->label->setStyleSheet(
              "border-image: url(:/head/Resources/ted-cruz.jpg)");
    } else {
        ui->label->setStyleSheet(
              "border-image:  url(:/head/Resources/John-Kasich-Headshot.jpg)");
    }
    this->move(250,150);

}
