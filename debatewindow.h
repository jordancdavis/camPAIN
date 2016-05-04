#ifndef DEBATEWINDOW_H
#define DEBATEWINDOW_H

#include <QWidget>
#include <QString>
#include <QTimer>
#include <question.h>
#include "mycanvas.h"
#include <SFML/Audio.hpp>

namespace Ui {
class DebateWindow;
}

class DebateWindow : public QWidget
{
    Q_OBJECT
    QString bernie;
    QString donald;
    QString hilary;
    QString john;
    QString ted;
    int userDebateVotes;
    int oppDebateVotes;
    int bonus;
    bool fight;
    MyCanvas* SFMLView;
    bool winner;

public:
    explicit DebateWindow(QWidget *parent = 0);
    ~DebateWindow();

signals:
    void switchToWindow(int);
    void candidateDefeated(int);

public slots:
    void showCandidates(int, int);
    void receiveQuestions(QList<Question>);
    void on_answerAButton_clicked();
    void on_answerBButton_clicked();
    void on_answerCButton_clicked();
    void on_answerDButton_clicked();
    void setVotes(int);
    void receivePhysics(float,float,float);
    void setStage(int);

private slots:
    void on_returnToMenuButton_clicked();
    void on_nextQuestionButton_clicked();
    void startFight();


private:
    Ui::DebateWindow *ui;
    int questionsAnswered;
    int maxQuestions;
    int correctQuestions;
    int correctAnswer;
    QList<Question> questions;
    QTimer* sleep;
    bool questionIsAnswered;
    void receivedAnswer();
    void setCurrentQuestion(int);
    void checkAnswer(int);
    void clearAnswerButtons();
    void youWin();
    void youLose();
    void endDebate();
    void questionAnswered();
    void questionNotAnswered();
    void updateVoteCount(bool);
    int initVotes;
    sf::Music music;
    sf::Music music2;
    int stageNum;

};

#endif // DEBATEWINDOW_H
