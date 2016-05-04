#include "startnewgamewindow.h"
#include "ui_startnewgamewindow.h"

StartNewGameWindow::StartNewGameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartNewGameWindow)
{
    ui->setupUi(this);
}

StartNewGameWindow::~StartNewGameWindow()
{
    delete ui;
}

void StartNewGameWindow::on_returnToMenuButton_clicked()
{
    //switch to gameMainMenuWindow
    emit switchToWindow(0);
}

void StartNewGameWindow::on_matchButton_clicked()
{
    //switch to compatabilityQuizWindow
    emit switchToWindow(5);

}

void StartNewGameWindow::on_userSelectButton_clicked()
{
    //switch to selectCharacterWindow
    emit switchToWindow(6);
}
