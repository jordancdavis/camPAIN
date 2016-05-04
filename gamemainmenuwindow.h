#ifndef GAMEMAINMENUWINDOW_H
#define GAMEMAINMENUWINDOW_H

#include <QWidget>

namespace Ui {
class GameMainMenuWindow;
}

class GameMainMenuWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameMainMenuWindow(QWidget *parent = 0);
    ~GameMainMenuWindow();

signals:
    void switchToWindow(int);
    void getStageList();
    void newGame();
    void getLeaderBoardFromDB();

private slots:
    void on_logoutButton_clicked();
    void on_continueGameButton_clicked();
    void on_startNewGameButton_clicked();
    void on_characterBioButton_clicked();
    void on_campainLeaderboardButton_clicked();
    void gameStatus(int);
    void receiveGameInfo(QStringList);
    void setVotes(int);

protected slots:
    void updateGameMenu();

private:
    Ui::GameMainMenuWindow *ui;
};

#endif // GAMEMAINMENUWINDOW_H
