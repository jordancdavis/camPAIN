#ifndef STARTNEWGAMEWINDOW_H
#define STARTNEWGAMEWINDOW_H

#include <QWidget>

namespace Ui {
class StartNewGameWindow;
}

class StartNewGameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StartNewGameWindow(QWidget *parent = 0);
    ~StartNewGameWindow();

signals:
    void switchToWindow(int);

private slots:
    void on_returnToMenuButton_clicked();
    void on_matchButton_clicked();
    void on_userSelectButton_clicked();

private:
    Ui::StartNewGameWindow *ui;
};

#endif // STARTNEWGAMEWINDOW_H
