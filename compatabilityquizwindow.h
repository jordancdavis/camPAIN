#ifndef COMPATABILITYQUIZWINDOW_H
#define COMPATABILITYQUIZWINDOW_H

#include <QWidget>

namespace Ui {
class CompatabilityQuizWindow;
}

class CompatabilityQuizWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CompatabilityQuizWindow(QWidget *parent = 0);
    ~CompatabilityQuizWindow();

signals:
    void switchToWindow(int);
    void candidateSelected(int);
    void getStageList();
    void CharacterBio1();
    void CharacterBio2();
    void CharacterBio3();
    void CharacterBio4();
    void CharacterBio5();

private slots:
    void on_returnToMenuButton_clicked();
    void on_answerAButton_clicked();
    void on_answerBButton_clicked();
    void on_answerCButton_clicked();

private:
    Ui::CompatabilityQuizWindow *ui;
    int questionsAnswered;
    int maxQuestions;
    int trumpScore;
    int hilaryScore;
    int sandersScore;
    int cruzScore;
    int kasichScore;
    void receivedAnswer();
};

#endif // COMPATABILITYQUIZWINDOW_H
