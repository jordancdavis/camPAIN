#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "continuedgamemenuwindow.h"
#include <QMainWindow>
#include <QApplication>
#include <QProcess>
#include <QMovie>
#include <SFML/Audio.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //create window widgets
    _gameMainMenuWindow = new GameMainMenuWindow();
    _continuedGameMenuWindow = new ContinuedGameMenuWindow();
    _startNewGameWindow = new StartNewGameWindow();
    _characterBioWindow = new CharacterBioWindow();
    _campainLeaderboardWindow = new CampainLeaderboardWindow();
    _compatabilityQuizWindow = new CompatabilityQuizWindow();
    _selectCharacterWindow = new SelectCharacterWindow();
    _debateWindow = new DebateWindow();

    //fill stack            (-1 to go back to main menu)
    _windows.addWidget(_gameMainMenuWindow);        //0
    _windows.addWidget(_continuedGameMenuWindow);   //1
    _windows.addWidget(_startNewGameWindow);        //2
    _windows.addWidget(_characterBioWindow);        //3
    _windows.addWidget(_campainLeaderboardWindow);  //4
    _windows.addWidget(_compatabilityQuizWindow);   //5
    _windows.addWidget(_selectCharacterWindow);     //6
    _windows.addWidget(_debateWindow);              //7
    _windows.move(0,0);
    mainMusic.openFromFile("/Users/Resources/Hail.ogg");
    mainMusic.setLoop(true);
    mainMusic.setVolume(20);
    mainMusic.play();


    QMovie *movie = new QMovie("/Users/Resources/WashingtonTwerk.gif");
    ui->processLabel->setMovie(movie);
    movie->start();

    QMovie *movie2 = new QMovie("/Users/Resources/LincolnTwerk.gif");
    ui->processLabel2->setMovie(movie2);
    movie2->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_signUpButton_clicked()
{
    _signupDialog.setModal(true);
    _signupDialog.exec();
}

void MainWindow::on_loginButton_clicked()
{
   _loginDialog.setModal(true);
   _loginDialog.exec();
}

void MainWindow::setMainWindowAs(int choice)
{
    int current = _windows.currentIndex();

    if(choice == -1){
        this->show();
        _windows.hide();
    } else {
        _windows.setCurrentIndex(choice);
        _windows.setStyleSheet("background-color:white;");
        if(choice == 1 || choice == 0){
            // -1 means no current game in progress
            emit updateCurrentGameStatus(_game.myCandidate);
        }
        if(choice == 7) {
            emit debatePlayers(_game.myCandidate,_game.opposingCandidate);
            mainMusic.stop();
        } else {
            if(current == 7){
                mainMusic.play();
            }
        }
        _windows.showNormal();
        _windows.update();
        this->hide();
        this->update();
    }

}
