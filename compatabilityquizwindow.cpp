#include "compatabilityquizwindow.h"
#include "ui_compatabilityquizwindow.h"
#include <QDebug>
#include <qglobal.h>
#include <QTime>

CompatabilityQuizWindow::CompatabilityQuizWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CompatabilityQuizWindow)
{
    ui->setupUi(this);
    questionsAnswered = 0;
    maxQuestions = 7;
    receivedAnswer();
}

CompatabilityQuizWindow::~CompatabilityQuizWindow()
{
    delete ui;
}

void CompatabilityQuizWindow::on_returnToMenuButton_clicked()
{
    //switch view to gameMainMenu
    emit switchToWindow(0);
    questionsAnswered = 0;
}

void CompatabilityQuizWindow::on_answerAButton_clicked() // Pro
{
    if(questionsAnswered == 1){
        kasichScore++;
        cruzScore++;
    } else if(questionsAnswered == 2) {
        kasichScore++;
        cruzScore++;
        trumpScore++;
        hilaryScore++;
    } else if(questionsAnswered == 3) {
        sandersScore++;
        hilaryScore++;
    } else if(questionsAnswered == 4) {
        cruzScore++;
    } else if(questionsAnswered == 5) {
        sandersScore++;
        hilaryScore++;
        kasichScore++;
    } else if(questionsAnswered == 6) {
        cruzScore++;
    } else if(questionsAnswered == 7) {
        sandersScore++;
        hilaryScore++;
    }
    receivedAnswer();
}

void CompatabilityQuizWindow::on_answerBButton_clicked() // Con
{
    if(questionsAnswered == 1){
        sandersScore++;
        trumpScore++;
    } else if(questionsAnswered == 2) {
        sandersScore++;
    } else if(questionsAnswered == 3) {
        cruzScore++;
        trumpScore++;
    } else if(questionsAnswered == 4) {
        kasichScore++;
        sandersScore++;
        trumpScore++;
        hilaryScore++;
    } else if(questionsAnswered == 5) {
        trumpScore++;
        cruzScore++;
    } else if(questionsAnswered == 6) {
        sandersScore++;
        kasichScore++;
        hilaryScore++;
    } else if(questionsAnswered == 7) {
        trumpScore++;
        kasichScore++;
        cruzScore++;
    }
    receivedAnswer();
}

void CompatabilityQuizWindow::on_answerCButton_clicked() // No Comment
{
    if(questionsAnswered == 1){
       hilaryScore++;
    } else if(questionsAnswered == 3) {
       kasichScore++;
    } else if(questionsAnswered == 6) {
       trumpScore++;
    }
    receivedAnswer();
}

void CompatabilityQuizWindow::receivedAnswer()
{
    //register answer       TODO
    if(questionsAnswered >= maxQuestions){
//        qDebug() << "Trump: " << trumpScore;
//        qDebug() << "Sanders: " << sandersScore;
//        qDebug() << "Clinton: " << hilaryScore;
//        qDebug() << "Cruz :" << cruzScore;
//        qDebug() << "Kasich :" << kasichScore;

        //determine top candidates
        int highScore = 0;
        if(trumpScore > highScore)
        {
            highScore = trumpScore;
        }
        if(sandersScore > highScore)
        {
            highScore = sandersScore;
        }
        if(hilaryScore > highScore)
        {
            highScore = hilaryScore;
        }
        if(cruzScore > highScore)
        {
            highScore = cruzScore;
        }
        if(kasichScore > highScore)
        {
            highScore = kasichScore;
        }

        QList<int> topCandidates = QList<int>();

        if(trumpScore == highScore)
        {
            topCandidates.push_back(1);
        }
        if(sandersScore == highScore)
        {
            topCandidates.push_back(0);
        }
        if(hilaryScore == highScore)
        {
            topCandidates.push_back(2);
        }
        if(cruzScore == highScore)
        {
            topCandidates.push_back(4);
        }
        if(kasichScore == highScore)
        {
            topCandidates.push_back(3);
        }

        //determine candidate from top candidates
        qsrand(QTime::currentTime().msec());
        int random = qrand();
        int candidateIndex = random % topCandidates.size();
        int candidate = topCandidates[candidateIndex];
        candidateSelected(candidate);

        // enable Continue button   TODO

        questionsAnswered = 1;
        sandersScore = 0;
        hilaryScore = 0;
        trumpScore = 0;
        cruzScore = 0;
        kasichScore = 0;
        ui->questionLabel->setText("Should the US Military budget be increased?");

        //switch view to continuedGameWindow
        if(candidate == 0)//Bernie
        {
            emit CharacterBio3();
        }
        else if(candidate == 1)//Donald
        {
            emit CharacterBio1();
        }
        else if(candidate == 2)//Hillary
        {
            emit CharacterBio2();
        }
        else if(candidate == 3)//Kasich
        {
            emit CharacterBio5();
        }
        else if(candidate == 4)//Cruz
        {
            emit CharacterBio4();
        }
        emit switchToWindow(1);
        emit getStageList();
    } else {
        //update display w/ new Q's and A's
        questionsAnswered++;
        if(questionsAnswered == 1){
            ui->questionLabel->setText("Should the US Military budget be increased?");
        } else if(questionsAnswered == 2) {
            ui->questionLabel->setText("Should the death penalty be allowed?");
        } else if(questionsAnswered == 3) {
            ui->questionLabel->setText("Should abortion be legal?");
        } else if(questionsAnswered == 4) {   // Ted Cruz Pro
            ui->questionLabel->setText("Should people on the no-fly list or terror watch list being allowed to purchase guns?");
        } else if(questionsAnswered == 5) {
            ui->questionLabel->setText("Should undocumented immigrants in the USA be allowed to become legal residents?");
        } else if(questionsAnswered == 6) {
            ui->questionLabel->setText("Should there be a flat tax on income?");
        } else if(questionsAnswered == 7) {
            ui->questionLabel->setText("Should the United States Allow Syrian Refugees into the Country?");
        }
    }
    this->update();
}

