#ifndef CAMPAINLEADERBOARDWINDOW_H
#define CAMPAINLEADERBOARDWINDOW_H

#include <QWidget>

namespace Ui {
class CampainLeaderboardWindow;
}

class CampainLeaderboardWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CampainLeaderboardWindow(QWidget *parent = 0);
    ~CampainLeaderboardWindow();

signals:
    void switchToWindow(int);

private slots:
    void on_returnToMenuButton_clicked();
    void on_globalLeaderboardButton_clicked();
    void on_pushButton_2_clicked();
    void receiveLeaderBoard(QList<QStringList>, QList<QStringList>);

private:
    Ui::CampainLeaderboardWindow *ui;
    QList<QStringList> globalLeaderboardList;
    QList<QStringList> groupLeaderboardList;
    void updateGlobalLeaderboard();
    void updateLocalLeaderboard();
};

#endif // CAMPAINLEADERBOARDWINDOW_H
