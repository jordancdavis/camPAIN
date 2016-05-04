#ifndef QUESTION_H
#define QUESTION_H
#include <QString>
#include <QList>

class Question
{
public:

    Question(int opposingCandidate, QStringList questionInfo, int seed);
    QString getQuestion();
    QList<QString> getAnswers();
    int getCorrectAnswer();

private:

    QString questionString;
    QList<QString> answers;
    int correctAnswer;
    // int rand;
    QString answerString;
    void setCorrectAnswer(int candidateToMatch, QList<QString> answerList, int seed);
    void setAnswers(QList<QString> oldList, int seed);
};

#endif // QUESTION_H
