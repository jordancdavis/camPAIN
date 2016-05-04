#include "selectcharacterwindow.h"
#include "ui_selectcharacterwindow.h"

SelectCharacterWindow::SelectCharacterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectCharacterWindow)
{
    ui->setupUi(this);
}

SelectCharacterWindow::~SelectCharacterWindow()
{
    delete ui;
}

void SelectCharacterWindow::on_returnToMenuButton_clicked()
{
    //switch to gameMainMenuWindow
    emit switchToWindow(0);
}

void SelectCharacterWindow::on_character1Button_clicked()
{
    //register selected character
    emit setCharacter(0);

    //switch to continuedGameWindow
    emit switchToWindow(1);
    emit getStageList();
}

void SelectCharacterWindow::on_character2Button_clicked()
{
    //register selected character
    emit setCharacter(1);

    //switch to continuedGameWindow
    emit switchToWindow(1);
    emit getStageList();
}

void SelectCharacterWindow::on_character3Button_clicked()
{
    //register selected character
    emit setCharacter(2);

    //switch to continuedGameWindow
    emit switchToWindow(1);
    emit getStageList();
}

void SelectCharacterWindow::on_character4Button_clicked()
{
    //register selected character
    emit setCharacter(3);

    //switch to continuedGameWindow
    emit switchToWindow(1);
    emit getStageList();
}

void SelectCharacterWindow::on_character5Button_clicked()
{
    //register selected character
    emit setCharacter(4);

    //switch to continuedGameWindow
    emit switchToWindow(1);
    emit getStageList();
}

