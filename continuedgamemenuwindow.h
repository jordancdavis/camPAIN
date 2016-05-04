#ifndef CONTINUEDGAMEMENUWINDOW_H
#define CONTINUEDGAMEMENUWINDOW_H

#include <QWidget>
#include <QString>
#include <QList>
#include "youwindialog.h"
#include "worldsettingswindow.h"

namespace Ui {
class ContinuedGameMenuWindow;
}

class ContinuedGameMenuWindow : public QWidget
{
    Q_OBJECT
    YouWinDialog _youWinDialog;

public:
    explicit ContinuedGameMenuWindow(QWidget *parent = 0);
    ~ContinuedGameMenuWindow();
    WorldSettingsWindow _worldSettingsWindow;
    float getGravity();
    float getOppBounce();
    float getBounce();

signals:
    void switchToWindow(int);
    void getStageList();
    void setOpponent(int);
    void getQuestions();
    void dropoutPlayer();
    void stageSelected(int);
    void updatePhysicsWorld(float, float, float);

private slots:
    void on_returnToMenuButton_clicked();
    void on_dropoutButton_clicked();
    void on_introductionButton_clicked();
    void on_stage1Button_clicked();
    void on_stage2Button_clicked();
    void on_stage3Button_clicked();
    void on_stage4Button_clicked();
    void updateStageList(QList<int>, QList<bool>);
    void receiveGameInfo(QStringList);
    void resetStageColors();
    void setVotes(int);
    void updatePlayerImage(int);
    void on_worldSettingsButton_clicked();

private:
    Ui::ContinuedGameMenuWindow *ui;
    QString getCandidateName(int);
    void setStageButtonColor(QList<int>, QList<bool>);
};

#endif // CONTINUEDGAMEMENUWINDOW_H
