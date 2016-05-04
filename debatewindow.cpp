#include "debatewindow.h"
#include "ui_debatewindow.h"
#include "mycanvas.h"
#include <QDebug>
#include <QTimer>
#include <SFML/Audio.hpp>

DebateWindow::DebateWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebateWindow)
{
    ui->setupUi(this);
    bernie = "border-image: url(:/head/Resources/BerniePainders5.png);";
    donald = "border-image: url(:/head/Resources/DonaldTrump5.png);";
    hilary = "border-image: url(:/head/Resources/Hillary5.png);";
    john = "border-image: url(:/head/Resources/John Kasichx5.png);";
    ted = "	border-image: url(:/head/Resources/TedCruzx5.png);";
    questionsAnswered = 0;
    correctQuestions = 0;
    userDebateVotes = 0;
    oppDebateVotes = 0;
    initVotes = 0;
    bonus = 1000;
    maxQuestions = 5;
    questionNotAnswered();
    sleep = new QTimer(this);
    sleep->setSingleShot(true);
    QObject::connect(sleep, SIGNAL(timeout()), this, SLOT(startFight()));
    music.openFromFile("/Users/Resources/RivalMusic.ogg");
    music.setLoop(true);
    music.setVolume(15);
    music2.openFromFile("/Users/Resources/Millionaire.ogg");
    music2.setLoop(true);
    winner = false;

}

DebateWindow::~DebateWindow()
{
    delete ui;
}

void DebateWindow::on_returnToMenuButton_clicked()
{
    //switch to continuedGameWindow
    endDebate();
    music2.stop();
    if(winner){
        emit candidateDefeated(userDebateVotes);
        winner = false;
    }
    setVotes(initVotes);
    emit switchToWindow(1);

}

void DebateWindow::showCandidates(int user, int opponent){
    SFMLView = new MyCanvas(this, QPoint(0, 0), QSize(1000, 425));
    SFMLView->setCandidates(user, opponent);
    SFMLView->show();
    music2.play();
    SFMLView->OnUpdate();
    if(user == 0){
           ui->playerButton->setStyleSheet(bernie);
       } else if (user == 1){
           ui->playerButton->setStyleSheet(donald);
       } else if (user == 2) {
           ui->playerButton->setStyleSheet(hilary);
       } else if (user == 3) {
           ui->playerButton->setStyleSheet(john);
       } else if (user == 4) {
           ui->playerButton->setStyleSheet(ted);
       }

       if(opponent == 0){
           ui->opponentButton->setStyleSheet(bernie);
       } else if (opponent == 1){
           ui->opponentButton->setStyleSheet(donald);
       } else if (opponent == 2) {
           ui->opponentButton->setStyleSheet(hilary);
       } else if (opponent == 3) {
           ui->opponentButton->setStyleSheet(john);
       } else if (opponent == 4) {
           ui->opponentButton->setStyleSheet(ted);
       }
}

void DebateWindow::receiveQuestions(QList<Question> questions)
{
    this->questions = questions;
    receivedAnswer();
}

void DebateWindow::setCurrentQuestion(int questionNum)
{
    ui->questionLabel->setText(questions[questionNum].getQuestion());
    ui->answerALabel->setText(questions[questionNum].getAnswers()[0]);
    ui->answerBLabel->setText(questions[questionNum].getAnswers()[1]);
    ui->answerCLabel->setText(questions[questionNum].getAnswers()[2]);
    ui->answerDLabel->setText(questions[questionNum].getAnswers()[3]);
    correctAnswer = questions[questionNum].getCorrectAnswer();
}

void DebateWindow::receivedAnswer()
{
    //register answer       TODO
    if(questionsAnswered >= maxQuestions){
        //end of debate stuff
    } else {
        questionsAnswered++;
        if(questionsAnswered == 1){
            setCurrentQuestion(0);
        } else if(questionsAnswered == 2) {
            setCurrentQuestion(1);
        } else if(questionsAnswered == 3) {
            setCurrentQuestion(2);
        } else if(questionsAnswered == 4) {
            setCurrentQuestion(3);
        } else if(questionsAnswered == 5) {
            setCurrentQuestion(4);
        }
    }
    this->update();
}

void DebateWindow::on_answerAButton_clicked() {
    if(!questionIsAnswered)
    {
        checkAnswer(0);
    }
}

void DebateWindow::on_answerBButton_clicked() {
    if(!questionIsAnswered)
    {
        checkAnswer(1);
    }
}

void DebateWindow::on_answerCButton_clicked() {
    if(!questionIsAnswered)
    {
        checkAnswer(2);
    }
}

void DebateWindow::on_answerDButton_clicked() {
    if(!questionIsAnswered)
    {
        checkAnswer(3);
    }
}

void DebateWindow::checkAnswer(int answer) {
    questionAnswered();
    if(answer == correctAnswer) {
        correctQuestions++;
        SFMLView->updateOpponentSpriteImage(correctQuestions-1);
        updateVoteCount(true);
    }
    else {
        updateVoteCount(false);
        if(answer == 0)
        {
            ui->answerAButton->setStyleSheet("background-color: red;border: 1px solid #000000;border-radius: 15px;");
        }
        else if(answer == 1)
        {
            ui->answerBButton->setStyleSheet("background-color: red;border: 1px solid #000000;border-radius: 15px;");
        }
        else if(answer == 2)
        {
            ui->answerCButton->setStyleSheet("background-color: red;border: 1px solid #000000;border-radius: 15px;");
        }
        else if(answer == 3)
        {
            ui->answerDButton->setStyleSheet("background-color: red;border: 1px solid #000000;border-radius: 15px;");
        }
    }
    if(correctAnswer == 0)
    {
        ui->answerAButton->setStyleSheet("background-color: green;border: 1px solid #000000;border-radius: 15px;");
        ui->answerAButton->update();

    }
    else if(correctAnswer == 1)
    {
        ui->answerBButton->setStyleSheet("background-color: green;border: 1px solid #000000;border-radius: 15px;");
        ui->answerBButton->update();

    }
    else if(correctAnswer == 2)
    {
        ui->answerCButton->setStyleSheet("background-color: green;border: 1px solid #000000;border-radius: 15px;");
        ui->answerCButton->update();

    }
    else if(correctAnswer == 3)
    {
        ui->answerDButton->setStyleSheet("background-color: green;border: 1px solid #000000;border-radius: 15px;");
        ui->answerDButton->update();
    }
    if(questionsAnswered == 5)
    {
        if(correctQuestions >= 3){
            youWin();
        } else {
            youLose();
        }
    }
    this->update();

    if (answer == correctAnswer)
    {
        //DONT CHANGE THIS ORDER
        music2.pause();
        music.play();
        sleep->start(1);    
    }
}

void DebateWindow::startFight(){
    //DONT CHANGE THIS ORDER
    //rounds 0-4 (keep the -1)
    SFMLView->Fight();
    music.stop();
    music2.play();
}

void DebateWindow::clearAnswerButtons()
{
    ui->answerAButton->setStyleSheet("QPushButton{background-color:white;border: 1px solid #000000;border-radius: 15px;}QPushButton:pressed{background-color:rgba(0, 145, 255, 128);}");
    ui->answerBButton->setStyleSheet("QPushButton{background-color:white;border: 1px solid #000000;border-radius: 15px;}QPushButton:pressed{background-color:rgba(0, 145, 255, 128);}");
    ui->answerCButton->setStyleSheet("QPushButton{background-color:white;border: 1px solid #000000;border-radius: 15px;}QPushButton:pressed{background-color:rgba(0, 145, 255, 128);}");
    ui->answerDButton->setStyleSheet("QPushButton{background-color:white;border: 1px solid #000000;border-radius: 15px;}QPushButton:pressed{background-color:rgba(0, 145, 255, 128);}");
}

void DebateWindow::on_nextQuestionButton_clicked()
{
    if(questionIsAnswered){
        if(questionsAnswered == 5)
        {
            if(winner){
                emit candidateDefeated(userDebateVotes);
                winner = false;
            }
            setVotes(initVotes);

            endDebate();
            music2.stop();
            emit switchToWindow(1);
            questionsAnswered = -1;
        }
        clearAnswerButtons();
        receivedAnswer();
        questionNotAnswered();
    }
}

void DebateWindow::youWin()
{
    ui->nextQuestionButton->setText("You Win");
    winner = true;
}

void DebateWindow::youLose()
{
    ui->nextQuestionButton->setText("You Lose");
    winner = false;
}

void DebateWindow::endDebate()
{
    questionsAnswered = 0;
    correctQuestions = 0;
    questionNotAnswered();
    clearAnswerButtons();
    ui->nextQuestionButton->setText("Next Question");
}

void DebateWindow::questionAnswered()
{
    questionIsAnswered = true;
    ui->nextQuestionButton->show();
    ui->answerAButton->setDisabled(true);
    ui->answerBButton->setDisabled(true);
    ui->answerCButton->setDisabled(true);
    ui->answerDButton->setDisabled(true);
}

void DebateWindow::questionNotAnswered()
{
    questionIsAnswered = false;
    ui->nextQuestionButton->hide();
    ui->answerAButton->setDisabled(false);
    ui->answerBButton->setDisabled(false);
    ui->answerCButton->setDisabled(false);
    ui->answerDButton->setDisabled(false);
}

void DebateWindow::setVotes(int numVotes)
{
    initVotes = numVotes;
    userDebateVotes = numVotes;
    oppDebateVotes = numVotes;
    ui->myVotesBar->setMinimum(userDebateVotes);
    ui->myVotesBar->setMaximum(userDebateVotes + (bonus * 5));
    ui->oppVotesBar->setMinimum(oppDebateVotes);
    ui->oppVotesBar->setMaximum(oppDebateVotes + (bonus * 5));
    ui->myVotesBar->setValue(userDebateVotes);
    ui->oppVotesBar->setValue(oppDebateVotes);
    ui->myVotesScore->setText(QString::number(userDebateVotes));
    ui->oppVotesScore->setText(QString::number(oppDebateVotes));
}

void DebateWindow::updateVoteCount(bool correct)
{
    if(correct){
        userDebateVotes += bonus;
        ui->myVotesBar->setValue(userDebateVotes);
        ui->myVotesScore->setText(QString::number(userDebateVotes));
    } else {
        oppDebateVotes += bonus;
        ui->oppVotesBar->setValue(oppDebateVotes);
        ui->oppVotesScore->setText(QString::number(oppDebateVotes));
    }
}

void DebateWindow::receivePhysics(float gravity, float bounce, float oppBounce){
    SFMLView->_gravity = gravity;
    SFMLView->_myBounce = bounce;
    SFMLView->_oppBounce = oppBounce;
}

void DebateWindow::setStage(int num){
    SFMLView->setStageNum(num);

}
