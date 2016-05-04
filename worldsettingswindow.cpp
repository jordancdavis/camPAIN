#include "worldsettingswindow.h"
#include "ui_worldsettingswindow.h"

WorldSettingsWindow::WorldSettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorldSettingsWindow)
{
    ui->setupUi(this);
    resetWindow();
}

WorldSettingsWindow::~WorldSettingsWindow()
{
    delete ui;
    ui->bounceSlider->setValue(1);
    ui->gravitySlider->setValue(9.8);
    ui->frictionSlider->setValue(1);
    gravity = 9.8f;
    bounce = 1.0f;
    oppBounce = 1.0f;
    updateLabels();
}

void WorldSettingsWindow::resetWindow() {
    this->move(250,150);
}

void WorldSettingsWindow::on_joinButton_clicked()
{
    this->close();
}

void WorldSettingsWindow::on_cancelButton_clicked()
{
    ui->bounceSlider->setValue(1);
    ui->gravitySlider->setValue(9.8);
    ui->frictionSlider->setValue(1);
    gravity = 9.8f;
    bounce = 1.0f;
    oppBounce = 1.0f;
    updateLabels();
}

void WorldSettingsWindow::on_gravitySlider_actionTriggered(int action)
{
    gravity = ui->gravitySlider->value()/10.0f;
    ui->gravLable->setText(QString::number(gravity));
}

void WorldSettingsWindow::on_bounceSlider_actionTriggered(int action)
{
    bounce = ui->bounceSlider->value()/10.0f;
    ui->fricLabel->setText(QString::number(bounce));
}

void WorldSettingsWindow::on_frictionSlider_actionTriggered(int action)
{
    oppBounce = ui->frictionSlider->value()/10.0f;
    ui->fricLabel->setText(QString::number(oppBounce));
}

void WorldSettingsWindow::updateLabels(){
    ui->gravLable->setText(QString::number(gravity));
    ui->bounceLabel->setText(QString::number(bounce));
    ui->fricLabel->setText(QString::number(oppBounce));
}
