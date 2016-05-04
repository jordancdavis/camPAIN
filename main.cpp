#include "mainwindow.h"
#include "gamemainmenuwindow.h"
#include "continuedgamemenuwindow.h"
#include "characterbiowindow.h"
#include "campainleaderboardwindow.h"
#include "question.h"
#include "myserver.h"
#include "client.h"
#include "webserver.h"
#include <QApplication>
#include <QList>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.move(0,0);
    w.show();

    // Start local server
    MyServer server;
    server.startServer();
    Client client;

    // Start Web Server
    WebServer webServer;
    webServer.startWebServer();

    //Allows navigation between views
    QObject::connect(w._gameMainMenuWindow, SIGNAL(switchToWindow(int)), &w, SLOT(setMainWindowAs(int)));
    QObject::connect(w._continuedGameMenuWindow, SIGNAL(switchToWindow(int)), &w, SLOT(setMainWindowAs(int)));
    QObject::connect(w._startNewGameWindow, SIGNAL(switchToWindow(int)), &w, SLOT(setMainWindowAs(int)));
    QObject::connect(w._characterBioWindow, SIGNAL(switchToWindow(int)), &w, SLOT(setMainWindowAs(int)));
    QObject::connect(w._campainLeaderboardWindow, SIGNAL(switchToWindow(int)), &w, SLOT(setMainWindowAs(int)));
    QObject::connect(w._compatabilityQuizWindow, SIGNAL(switchToWindow(int)), &w, SLOT(setMainWindowAs(int)));
    QObject::connect(w._selectCharacterWindow, SIGNAL(switchToWindow(int)), &w, SLOT(setMainWindowAs(int)));
    QObject::connect(w._debateWindow, SIGNAL(switchToWindow(int)), &w, SLOT(setMainWindowAs(int)));

    //Connects selectCharacterWindow to model
    QObject::connect(w._selectCharacterWindow, SIGNAL(setCharacter(int)), &w._game, SLOT(setCharacter(int)));
    QObject::connect(w._selectCharacterWindow, SIGNAL(getStageList()), &w._game, SLOT(getStageList()));

    //Connects gameMainMenuWindow to continuedGameMenuWindow
    QObject::connect(w._gameMainMenuWindow, SIGNAL(newGame()), &w._game, SLOT(playerDroppedOut()));


    //Connects gameMainMenuWindow to model
    QObject::connect(w._gameMainMenuWindow, SIGNAL(getStageList()), &w._game, SLOT(getStageList()));

    //Connects continuedGameMenuWindow to model
    QObject::connect(&w._game, SIGNAL(returnStageList(QList<int>, QList<bool>)), w._continuedGameMenuWindow, SLOT(updateStageList(QList<int>, QList<bool>)));
    QObject::connect(w._continuedGameMenuWindow, SIGNAL(setOpponent(int)), &w._game, SLOT(updateOpponent(int)));
    QObject::connect(w._continuedGameMenuWindow, SIGNAL(dropoutPlayer()), &w._game, SLOT(playerDroppedOut()));
    QObject::connect(&w._game, SIGNAL(resetStageColors()), w._continuedGameMenuWindow, SLOT(resetStageColors()));
    QObject::connect(&w._game, SIGNAL(setVotes(int)), w._continuedGameMenuWindow, SLOT(setVotes(int)));

    //Connects compatabilityQuizWindow to model
    QObject::connect(w._compatabilityQuizWindow, SIGNAL(candidateSelected(int)), &w._game, SLOT(setCharacter(int)));
    QObject::connect(w._compatabilityQuizWindow, SIGNAL(getStageList()), &w._game, SLOT(getStageList()));

    //Connects model to client for dropout
    QObject::connect(&w._game, SIGNAL(dropoutWithUsername(QString)), &client, SLOT(dropoutUser(QString)));

    //Connects model to client for character selection
    QObject::connect(&w._game, SIGNAL(sendCharacterSelectionToDB(QString, int)), &client, SLOT(characterSelected(QString, int)));

    //Connects model to client to send votes
    QObject::connect(&w._game, SIGNAL(sendScoreToDB(QString, int, int)), &client, SLOT(updateScore(QString, int, int)));

    //Connects model to client to get leader board
    QObject::connect(&w._game, SIGNAL(getLeaderBoardWithGroupID(QString)), &client, SLOT(getLeaderBoardWithGroupID(QString)));

    //Connects client to campainLeaderBoard to send leader board
    QObject::connect(&client, SIGNAL(returnLeaderBoard(QList<QStringList>, QList<QStringList>)), w._campainLeaderboardWindow, SLOT(receiveLeaderBoard(QList<QStringList>, QList<QStringList>)));


    //Connects compatabilityQuizWindow to bioDialog
    QObject::connect(w._compatabilityQuizWindow, SIGNAL(CharacterBio1()), w._characterBioWindow, SLOT(on_character1Button_clicked()));
    QObject::connect(w._compatabilityQuizWindow, SIGNAL(CharacterBio2()), w._characterBioWindow, SLOT(on_character2Button_clicked()));
    QObject::connect(w._compatabilityQuizWindow, SIGNAL(CharacterBio3()), w._characterBioWindow, SLOT(on_character3Button_clicked()));
    QObject::connect(w._compatabilityQuizWindow, SIGNAL(CharacterBio4()), w._characterBioWindow, SLOT(on_character4Button_clicked()));
    QObject::connect(w._compatabilityQuizWindow, SIGNAL(CharacterBio5()), w._characterBioWindow, SLOT(on_character5Button_clicked()));

    //Connects model to debatewindow
    QObject::connect(&w, SIGNAL(debatePlayers(int, int)), w._debateWindow, SLOT(showCandidates(int,int)));

    //Connects model to gameMainMenuWindow
    QObject::connect(&w, SIGNAL(updateCurrentGameStatus(int)), w._gameMainMenuWindow, SLOT(gameStatus(int)));
    QObject::connect(&w, SIGNAL(updateCurrentGameStatus(int)), w._continuedGameMenuWindow, SLOT(updatePlayerImage(int)));
    QObject::connect(w._gameMainMenuWindow, SIGNAL(getLeaderBoardFromDB()), &w._game, SLOT(getLeaderBoardFromDB()));
    QObject::connect(&w._game, SIGNAL(setVotes(int)), w._gameMainMenuWindow, SLOT(setVotes(int)));

    //Connects continuedGameMenuWindow to client
    QObject::connect(w._continuedGameMenuWindow, SIGNAL(getQuestions()), &client, SLOT(getNewQuestion()));

    // used for testing without database
//    QObject::connect(w._continuedGameMenuWindow, SIGNAL(getQuestions()), &w._game, SLOT(getQuestions()));


    //Connects client to model
    QObject::connect(&client, SIGNAL(sendQuestionsToModel(QList<QStringList>)), &w._game, SLOT(receiveQuestionFromDB(QList<QStringList>)));

    // used for testing without database
//    QObject::connect(&w._game, SIGNAL(returnQuestionsFromDB(QList<QStringList>)), &w._game, SLOT(receiveQuestionFromDB(QList<QStringList>)));


    //Connects model to debateWindow
    QObject::connect(&w._game, SIGNAL(returnQuestions(QList<Question>)), w._debateWindow, SLOT(receiveQuestions(QList<Question>)));
    QObject::connect(&w._game, SIGNAL(setVotes(int)), w._debateWindow, SLOT(setVotes(int)));

    //Connects signupDialog to server
    QObject::connect(&w._signupDialog, SIGNAL(joinButtonClicked(QString,QString,QString,QString, bool)), &client, SLOT(sendNewAccountInfo(QString,QString,QString,QString, bool)));

    //Connects loginDialog to server
    QObject::connect(&w._loginDialog, SIGNAL(loginButtonClicked(QString,QString)), &client, SLOT(loginAccount(QString,QString)));
    QObject::connect(&w._loginDialog, SIGNAL(switchToWindow(int)), &w, SLOT(setMainWindowAs(int)));

    //Connects server to loginDialog
    QObject::connect(&client, SIGNAL(sendAccountInfoToModel(QStringList)), &w._loginDialog, SLOT(receiveLoginInfo(QStringList)));

    //Connects loginDialog to gamemainmenuwindow and continuedgamemenuwindow and game
    QObject::connect(&w._loginDialog, SIGNAL(sendGameInfo(QStringList)), w._gameMainMenuWindow, SLOT(receiveGameInfo(QStringList)));
    QObject::connect(&w._loginDialog, SIGNAL(sendGameInfo(QStringList)), w._continuedGameMenuWindow, SLOT(receiveGameInfo(QStringList)));
    QObject::connect(&w._loginDialog, SIGNAL(sendGameInfo(QStringList)), &w._game, SLOT(receiveGameInfo(QStringList)));

    //Connects debateWindow to model
    QObject::connect(w._debateWindow, SIGNAL(candidateDefeated(int)), &w._game, SLOT(candidateDefeated(int)));

    //Connects ContinuedGameMenu(settings) to debateWindow / canvas
    QObject::connect(w._continuedGameMenuWindow, SIGNAL(updatePhysicsWorld(float,float,float)), w._debateWindow, SLOT(receivePhysics(float,float,float)));
    QObject::connect(w._continuedGameMenuWindow, SIGNAL(stageSelected(int)), w._debateWindow, SLOT(setStage(int)));

    QObject::connect(&client, SIGNAL(newAccountResultMessage(QString)), &w._signupDialog, SLOT(checkSignupErrors(QString)));


    return a.exec();
}

