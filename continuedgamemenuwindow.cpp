#include "continuedgamemenuwindow.h"
#include "ui_continuedgamemenuwindow.h"
#include <QDebug>
#include <QMovie>

ContinuedGameMenuWindow::ContinuedGameMenuWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContinuedGameMenuWindow)
{
    ui->setupUi(this);
    QMovie *movie = new QMovie("/Users/Resources/Usa-flag.gif");
    ui->FlagLabel->setMovie(movie);
    movie->start();
}

ContinuedGameMenuWindow::~ContinuedGameMenuWindow()
{
    delete ui;
}

void ContinuedGameMenuWindow::on_returnToMenuButton_clicked()
{
    emit switchToWindow(0);
}

void ContinuedGameMenuWindow::on_dropoutButton_clicked()
{
   //disable continue button and set current character to -1
   emit dropoutPlayer();

   //switch to gameMainMenuWidnow
   emit switchToWindow(0);
}

void ContinuedGameMenuWindow::on_introductionButton_clicked()
{
    //switch to debate window
    emit setOpponent(0);
    emit switchToWindow(7);
    emit getQuestions();
    emit stageSelected(0);
    emit updatePhysicsWorld(getGravity(), getBounce(), getOppBounce());
}

void ContinuedGameMenuWindow::on_stage1Button_clicked()
{
    //switch to debate window
    emit setOpponent(1);
    emit switchToWindow(7);
    emit getQuestions();
    emit stageSelected(1);
    emit updatePhysicsWorld(getGravity(), getBounce(), getOppBounce());

}

void ContinuedGameMenuWindow::on_stage2Button_clicked()
{
    //switch to debate window
    emit setOpponent(2);
    emit switchToWindow(7);
    emit getQuestions();
    emit stageSelected(2);
    emit updatePhysicsWorld(getGravity(), getBounce(), getOppBounce());

}

void ContinuedGameMenuWindow::on_stage3Button_clicked()
{
    //switch to debate window
    emit setOpponent(3);
    emit switchToWindow(7);
    emit getQuestions();
    emit stageSelected(3);
    emit updatePhysicsWorld(getGravity(), getBounce(), getOppBounce());
}

void ContinuedGameMenuWindow::on_stage4Button_clicked()
{
    //switch to debate window
    emit setOpponent(4);
    emit switchToWindow(7);
    emit getQuestions();
    emit stageSelected(4);
    emit updatePhysicsWorld(getGravity(), getBounce(), getOppBounce());
}

QString ContinuedGameMenuWindow::getCandidateName(int candidateNum)
{
    QString candidate = "";
    if(candidateNum == 0)
    {
        candidate = "Bernie Sanders";
    }
    else if(candidateNum == 1)
    {
        candidate = "Donald Trump";
    }
    else if(candidateNum == 2)
    {
        candidate = "Hillary Clinton";
    }
    else if(candidateNum == 3)
    {
        candidate = "John Kasich";
    }
    else if(candidateNum == 4)
    {
        candidate = "Ted Cruz";
    }
    return candidate;
}

void ContinuedGameMenuWindow::updateStageList(QList<int> stageList, QList<bool> stageStatus)
{
    ui->stage1Button->setText(getCandidateName(stageList[1]));
    ui->stage2Button->setText(getCandidateName(stageList[2]));
    ui->stage3Button->setText(getCandidateName(stageList[3]));
    ui->stage4Button->setText(getCandidateName(stageList[4]));
    setStageButtonColor(stageList, stageStatus);
    //TODO
    //SET BUTTON COLORS
    //GO BACK TO QLIST<QLIST<INT>> WITH CANDIDATE && T/F
}

void ContinuedGameMenuWindow::setStageButtonColor(QList<int> stageList, QList<bool> stageStatus)
{
    int levelCount = 0;
    //stageStatus in first name order
    if(stageStatus[stageList[0]] == true) // 1 = isDefeated
    {
        ui->introductionButton->setStyleSheet("background-color: green;border: 1px solid #000000;border-radius: 15px;");
        ui->introductionButton->setEnabled(false);//disable button
        levelCount++;
    }
    if(stageStatus[stageList[1]] == true) // 1 = isDefeated
    {
        ui->stage1Button->setStyleSheet("background-color: green;border: 1px solid #000000;border-radius: 15px;");
        ui->stage1Button->setEnabled(false);//disable button
        levelCount++;
    }
    if(stageStatus[stageList[2]] == true) // 1 = isDefeated
    {
        ui->stage2Button->setStyleSheet("background-color: green;border: 1px solid #000000;border-radius: 15px;");
        ui->stage2Button->setEnabled(false);//disable button
        levelCount++;
    }
    if(stageStatus[stageList[3]] == true) // 1 = isDefeated
    {
        ui->stage3Button->setStyleSheet("background-color: green;border: 1px solid #000000;border-radius: 15px;");
        ui->stage3Button->setEnabled(false);//disable button
        levelCount++;
    }
    if(stageStatus[stageList[4]] == true) // 1 = isDefeated
    {
        ui->stage4Button->setStyleSheet("background-color: green;border: 1px solid #000000;border-radius: 15px;");
        ui->stage4Button->setEnabled(false);//disable button
        levelCount++;
    }

    if(levelCount == 5){
        _youWinDialog.setModal(true);
        _youWinDialog.exec();
    }
}

void ContinuedGameMenuWindow::receiveGameInfo(QStringList loginInfo)
{
    ui->usernameLabel->setText("username: " + loginInfo[0]);
    ui->highScoreLabel->setText("high score: " + loginInfo[1]);
    ui->totalVotesLabel->setText("votes: " + loginInfo[2]);
    //groupLabel setText...
}

void ContinuedGameMenuWindow::resetStageColors()
{
    ui->introductionButton->setStyleSheet("QPushButton{color:blue;border: 1px solid #000000;border-radius: 15px;}QPushButton:pressed{color:red;background-color:rgba(0, 145, 255, 128);}");
    ui->stage1Button->setStyleSheet("QPushButton{color:blue;border: 1px solid #000000;border-radius: 15px;}QPushButton:pressed{color:red;background-color:rgba(0, 145, 255, 128);}");
    ui->stage2Button->setStyleSheet("QPushButton{color:blue;border: 1px solid #000000;border-radius: 15px;}QPushButton:pressed{color:red;background-color:rgba(0, 145, 255, 128);}");
    ui->stage3Button->setStyleSheet("QPushButton{color:blue;border: 1px solid #000000;border-radius: 15px;}QPushButton:pressed{color:red;background-color:rgba(0, 145, 255, 128);}");
    ui->stage4Button->setStyleSheet("QPushButton{color:blue;border: 1px solid #000000;border-radius: 15px;}QPushButton:pressed{color:red;background-color:rgba(0, 145, 255, 128);}");

    ui->introductionButton->setEnabled(true);
    ui->stage1Button->setEnabled(true);
    ui->stage2Button->setEnabled(true);
    ui->stage3Button->setEnabled(true);
    ui->stage4Button->setEnabled(true);
}

void ContinuedGameMenuWindow::setVotes(int votes)
{
    int highScore = ui->highScoreLabel->text().toInt();
    ui->highScoreLabel->setText("high score: " + QString::number(votes+highScore));
    ui->totalVotesLabel->setText("votes: " + QString::number(votes));
}

void ContinuedGameMenuWindow::updatePlayerImage(int img)
{
    if(img == 0){
        ui->myCharacterLabel->setStyleSheet("border-image:url(:/head/Resources/BerniePainders5.png); ");
    } else if(img == 1){
        ui->myCharacterLabel->setStyleSheet("border-image:url(:/head/Resources/DonaldTrump5.png);");
    }else if(img == 2){
        ui->myCharacterLabel->setStyleSheet("border-image:url(:/head/Resources/Hillary5.png);");
    }else if(img == 3){
        ui->myCharacterLabel->setStyleSheet("border-image:url(:/head/Resources/John Kasichx5.png);");
    }else if(img == 4){
        ui->myCharacterLabel->setStyleSheet("border-image:url(:/head/Resources/TedCruzx5.png);");
    }
}

void ContinuedGameMenuWindow::on_worldSettingsButton_clicked()
{
    _worldSettingsWindow.setModal(true);
    _worldSettingsWindow.exec();
}

float ContinuedGameMenuWindow::getGravity(){
    return _worldSettingsWindow.gravity;
}

float ContinuedGameMenuWindow::getBounce(){
    return _worldSettingsWindow.bounce;
}

float ContinuedGameMenuWindow::getOppBounce(){
    return _worldSettingsWindow.oppBounce;
}
