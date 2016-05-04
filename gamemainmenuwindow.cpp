#include "gamemainmenuwindow.h"
#include "ui_gamemainmenuwindow.h"
#include "mainwindow.h"

GameMainMenuWindow::GameMainMenuWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::GameMainMenuWindow)
{
    ui->setupUi(this);
}

GameMainMenuWindow::~GameMainMenuWindow()
{
    delete ui;
}

void GameMainMenuWindow::on_logoutButton_clicked()
{
    //send signal to return to main menu        TODO
    //make sure progress is saved and logout.   TODO

    //switch back to login/signup window
    emit switchToWindow(-1);
}

void GameMainMenuWindow::on_continueGameButton_clicked()
{
    //switch to continuedGameWindow
    emit switchToWindow(1);
    emit getStageList();
}

void GameMainMenuWindow::on_startNewGameButton_clicked()
{
    //switch to startNewGameWindow
    emit switchToWindow(2);
    emit newGame();

}

void GameMainMenuWindow::on_characterBioButton_clicked()
{
    //switch to characterBioWindow
    emit switchToWindow(3);
}

void GameMainMenuWindow::on_campainLeaderboardButton_clicked()
{
    //switch to leaderboardWindow
    emit switchToWindow(4);
    emit getLeaderBoardFromDB();
}

void GameMainMenuWindow::updateGameMenu()
{
    //switch to gameMainMenuWindow
    emit switchToWindow(0);
}

void GameMainMenuWindow::gameStatus(int status) {
    //if status == -1 then no character selects / no game in progress.
    if(status == -1){
        ui->continueGameButton->setEnabled(false);
        ui->continueGameButton->setStyleSheet("QPushButton{border: 1px solid #000000;border-radius: 15px;}");
    } else {
        ui->continueGameButton->setEnabled(true);
        ui->continueGameButton->setStyleSheet("QPushButton{color:blue;border: 1px solid #000000;border-radius: 15px;}QPushButton:pressed{color:red;background-color:rgba(0, 145, 255, 128);}");
    }
}

void GameMainMenuWindow::receiveGameInfo(QStringList loginInfo)
{
    ui->usernameLabel->setText("username: " + loginInfo[0]);
    ui->highScoreLabel->setText("high score: " + loginInfo[1]);
    ui->totalVotesLabel->setText("votes: " + loginInfo[2]);
}

void GameMainMenuWindow::setVotes(int votes)
{
    int highScore = ui->highScoreLabel->text().toInt();
    ui->highScoreLabel->setText("high score: " + QString::number(votes + highScore));
    ui->totalVotesLabel->setText("votes: " + QString::number(votes));
}
