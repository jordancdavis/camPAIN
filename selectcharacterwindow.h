#ifndef SELECTCHARACTERWINDOW_H
#define SELECTCHARACTERWINDOW_H

#include <QWidget>

namespace Ui {
class SelectCharacterWindow;
}

class SelectCharacterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SelectCharacterWindow(QWidget *parent = 0);
    ~SelectCharacterWindow();

signals:
    void switchToWindow(int);
    void setCharacter(int);
    void getStageList();

private slots:
    void on_returnToMenuButton_clicked();
    void on_character1Button_clicked();
    void on_character2Button_clicked();
    void on_character3Button_clicked();
    void on_character4Button_clicked();
    void on_character5Button_clicked();

private:
    Ui::SelectCharacterWindow *ui;
};

#endif // SELECTCHARACTERWINDOW_H
