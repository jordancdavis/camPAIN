#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "signupdialog.h"
#include "gamemainmenuwindow.h"
#include "continuedgamemenuwindow.h"
#include "startnewgamewindow.h"
#include "characterbiowindow.h"
#include "campainleaderboardwindow.h"
#include "compatabilityquizwindow.h"
#include "selectcharacterwindow.h"
#include "debatewindow.h"
#include "game.h"
#include "logindialog.h"
#include <QStackedWidget>
#include <SFML/Audio.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    SignUpDialog _signupDialog;
    LoginDialog _loginDialog;
    QWidget* _gameMainMenuWindow;
    QWidget* _continuedGameMenuWindow;
    QWidget* _startNewGameWindow;
    QWidget* _characterBioWindow;
    QWidget* _campainLeaderboardWindow;
    QWidget* _compatabilityQuizWindow;
    QWidget* _selectCharacterWindow;
    QWidget* _debateWindow;
    QStackedWidget _windows;
    Game _game;

signals:
    void debatePlayers(int, int);
    void updateCurrentGameStatus(int);

public slots:
    void setMainWindowAs(int);

private slots:
    void on_signUpButton_clicked();
    void on_loginButton_clicked();

private:
    Ui::MainWindow *ui;
    sf::Music mainMusic;
};

#endif // MAINWINDOW_H
