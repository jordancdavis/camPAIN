#ifndef CHARACTERBIOWINDOW_H
#define CHARACTERBIOWINDOW_H

#include "biodialog.h"
#include <QWidget>

namespace Ui {
class CharacterBioWindow;
}

class CharacterBioWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterBioWindow(QWidget *parent = 0);
    ~CharacterBioWindow();

signals:
    void switchToWindow(int);

private slots:
    void on_returnToMenuButton_clicked();
    void on_character1Button_clicked();
    void on_character2Button_clicked();
    void on_character3Button_clicked();
    void on_character4Button_clicked();
    void on_character5Button_clicked();

private:
    Ui::CharacterBioWindow *ui;
};

#endif // CHARACTERBIOWINDOW_H
