#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QList>
#include <QString>
#include <QStringList>
#include "question.h"

using namespace std;

class Game : public QObject
{
public:
    explicit Game(QObject *parent = 0);

    int votes;
    int myCandidate;
    int opposingCandidate;
    QString groupID;
    QList<Question> currentQuestions;
    QList<bool> candidatesDefeated;
    QList<int> levelOrder;

signals:
    void returnStageList(QList<int>, QList<bool>);
    void checkedAnswer(bool, int);
    void winLevel(int);
    void loseLevel(int);
    void returnQuestionsFromDB(QList<QStringList>);
    void returnQuestions(QList<Question>);
    void dropoutWithUsername(QString);
    void resetStageColors();
    void sendCharacterSelectionToDB(QString, int);
    void sendScoreToDB(QString, int, int);
    void getLeaderBoardWithGroupID(QString);
    void setVotes(int);

public slots:
    void setCharacter(int);
    void getStageList();
    void updateOpponent(int);
    void checkAnswer(int);
    void getQuestions(); //move this to client
    void receiveQuestionFromDB(QList<QStringList>);
    void playerDroppedOut();
    void receiveGameInfo(QStringList);
    void candidateDefeated(int);
    void getLeaderBoardFromDB();

private:
    void setLevelOrder();
    void currentLevelStatus();
    int correctCount;
    int currentQuestion;
    int correctAnswer;
    QString playerUsername;

    Q_OBJECT
};

#endif

