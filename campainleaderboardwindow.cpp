#include "campainleaderboardwindow.h"
#include "ui_campainleaderboardwindow.h"
#include <QMovie>

CampainLeaderboardWindow::CampainLeaderboardWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CampainLeaderboardWindow)
{
    ui->setupUi(this);

    QMovie *movie = new QMovie("/Users/Resources/samFlying.gif");
    ui->samLabel->setMovie(movie);
    movie->start();
}

CampainLeaderboardWindow::~CampainLeaderboardWindow()
{
    delete ui;
}

void CampainLeaderboardWindow::on_returnToMenuButton_clicked()
{
    //switch view to gameMainMenu
    emit switchToWindow(0);
}

void CampainLeaderboardWindow::on_globalLeaderboardButton_clicked()
{
    ui->groupBox->setTitle("Global Leaderboard");

    //this method updates the gui. needs to be completed
    updateGlobalLeaderboard();
}

void CampainLeaderboardWindow::on_pushButton_2_clicked()
{
    ui->groupBox->setTitle("Group Leaderboard");

    //this method updates the gui. needs to be completed
    updateLocalLeaderboard();
}

void CampainLeaderboardWindow::updateLocalLeaderboard()
{
    if(groupLeaderboardList.size() > 0)
    {
        ui->usernameLabel1->setText(groupLeaderboardList[0][0]);
        ui->scoreLabel1->setText(groupLeaderboardList[0][1]);
    }
    else
    {
        ui->usernameLabel1->setText("");
        ui->scoreLabel1->setText("");
    }

    if(groupLeaderboardList.size() > 1)
    {
        ui->usernameLabel2->setText(groupLeaderboardList[1][0]);
        ui->scoreLabel2->setText(groupLeaderboardList[1][1]);
    }
    else
    {
        ui->usernameLabel2->setText("");
        ui->scoreLabel2->setText("");
    }

    if(groupLeaderboardList.size() > 2)
    {
        ui->usernameLabel3->setText(groupLeaderboardList[2][0]);
        ui->scoreLabel3->setText(groupLeaderboardList[2][1]);
    }
    else
    {
        ui->usernameLabel3->setText("");
        ui->scoreLabel3->setText("");
    }

    if(groupLeaderboardList.size() > 3)
    {
        ui->usernameLabel4->setText(groupLeaderboardList[3][0]);
        ui->scoreLabel4->setText(groupLeaderboardList[3][1]);
    }
    else
    {
        ui->usernameLabel4->setText("");
        ui->scoreLabel4->setText("");
    }

    if(groupLeaderboardList.size() > 4)
    {
        ui->usernameLabel5->setText(groupLeaderboardList[4][0]);
        ui->scoreLabel5->setText(groupLeaderboardList[4][1]);
    }
    else
    {
        ui->usernameLabel5->setText("");
        ui->scoreLabel5->setText("");
    }

    if(groupLeaderboardList.size() > 5)
    {
        ui->usernameLabel6->setText(groupLeaderboardList[5][0]);
        ui->scoreLabel6->setText(groupLeaderboardList[5][1]);
    }
    else
    {
        ui->usernameLabel6->setText("");
        ui->scoreLabel6->setText("");
    }

    if(groupLeaderboardList.size() > 6)
    {
        ui->usernameLabel7->setText(groupLeaderboardList[6][0]);
        ui->scoreLabel7->setText(groupLeaderboardList[6][1]);
    }
    else
    {
        ui->usernameLabel7->setText("");
        ui->scoreLabel7->setText("");
    }

    if(groupLeaderboardList.size() > 7)
    {
        ui->usernameLabel8->setText(groupLeaderboardList[7][0]);
        ui->scoreLabel8->setText(groupLeaderboardList[7][1]);
    }
    else
    {
        ui->usernameLabel8->setText("");
        ui->scoreLabel8->setText("");
    }

    if(groupLeaderboardList.size() > 8)
    {
        ui->usernameLabel9->setText(groupLeaderboardList[8][0]);
        ui->scoreLabel9->setText(groupLeaderboardList[8][1]);
    }
    else
    {
        ui->usernameLabel9->setText("");
        ui->scoreLabel9->setText("");
    }

    if(groupLeaderboardList.size() > 9)
    {
        ui->usernameLabel10->setText(groupLeaderboardList[9][0]);
        ui->scoreLabel10->setText(groupLeaderboardList[9][1]);
    }
    else
    {
        ui->usernameLabel10->setText("");
        ui->scoreLabel10->setText("");
    }
}

void CampainLeaderboardWindow::updateGlobalLeaderboard()
{
    if(globalLeaderboardList.size() > 0)
    {
        ui->usernameLabel1->setText(globalLeaderboardList[0][0]);
        ui->scoreLabel1->setText(globalLeaderboardList[0][1]);
    }
    else
    {
        ui->usernameLabel1->setText("");
        ui->scoreLabel1->setText("");
    }

    if(globalLeaderboardList.size() > 1)
    {
        ui->usernameLabel2->setText(globalLeaderboardList[1][0]);
        ui->scoreLabel2->setText(globalLeaderboardList[1][1]);
    }
    else
    {
        ui->usernameLabel2->setText("");
        ui->scoreLabel2->setText("");
    }

    if(globalLeaderboardList.size() > 2)
    {
        ui->usernameLabel3->setText(globalLeaderboardList[2][0]);
        ui->scoreLabel3->setText(globalLeaderboardList[2][1]);
    }
    else
    {
        ui->usernameLabel3->setText("");
        ui->scoreLabel3->setText("");
    }

    if(globalLeaderboardList.size() > 3)
    {
        ui->usernameLabel4->setText(globalLeaderboardList[3][0]);
        ui->scoreLabel4->setText(globalLeaderboardList[3][1]);
    }
    else
    {
        ui->usernameLabel4->setText("");
        ui->scoreLabel4->setText("");
    }

    if(globalLeaderboardList.size() > 4)
    {
        ui->usernameLabel5->setText(globalLeaderboardList[4][0]);
        ui->scoreLabel5->setText(globalLeaderboardList[4][1]);
    }
    else
    {
        ui->usernameLabel5->setText("");
        ui->scoreLabel5->setText("");
    }

    if(globalLeaderboardList.size() > 5)
    {
        ui->usernameLabel6->setText(globalLeaderboardList[5][0]);
        ui->scoreLabel6->setText(globalLeaderboardList[5][1]);
    }
    else
    {
        ui->usernameLabel6->setText("");
        ui->scoreLabel6->setText("");
    }

    if(globalLeaderboardList.size() > 6)
    {
        ui->usernameLabel7->setText(globalLeaderboardList[6][0]);
        ui->scoreLabel7->setText(globalLeaderboardList[6][1]);
    }
    else
    {
        ui->usernameLabel7->setText("");
        ui->scoreLabel7->setText("");
    }

    if(globalLeaderboardList.size() > 7)
    {
        ui->usernameLabel8->setText(globalLeaderboardList[7][0]);
        ui->scoreLabel8->setText(globalLeaderboardList[7][1]);
    }
    else
    {
        ui->usernameLabel8->setText("");
        ui->scoreLabel8->setText("");
    }

    if(globalLeaderboardList.size() > 8)
    {
        ui->usernameLabel9->setText(globalLeaderboardList[8][0]);
        ui->scoreLabel9->setText(globalLeaderboardList[8][1]);
    }
    else
    {
        ui->usernameLabel9->setText("");
        ui->scoreLabel9->setText("");
    }

    if(globalLeaderboardList.size() > 9)
    {
        ui->usernameLabel10->setText(globalLeaderboardList[9][0]);
        ui->scoreLabel10->setText(globalLeaderboardList[9][1]);
    }
    else
    {
        ui->usernameLabel10->setText("");
        ui->scoreLabel10->setText("");
    }
}

void CampainLeaderboardWindow::receiveLeaderBoard(QList<QStringList> leaderBoardGlobalList, QList<QStringList> leaderBoardGroupList)
{
    globalLeaderboardList = leaderBoardGlobalList;
    groupLeaderboardList = leaderBoardGroupList;
    if (groupLeaderboardList[0][0] == "")
    {
        ui->pushButton_2->setDisabled(true);
    }
    else
    {
        ui->pushButton_2->setDisabled(false);
    }
    updateGlobalLeaderboard();
}
