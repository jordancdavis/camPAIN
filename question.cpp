#include "Question.h"
#include <QDebug>
#include <QTime>

//2016 CS3505 CamPAIN educational game


/**
 * Creates a question object that contains a QString holding the question,
 * a QList<String> holding 4 answers and an int correctAnswer that indictated the
 * index in the QList of the correct answer to the question.
 * @brief question::question
 * @param opposingCandidate
 * @param questionInfo
 */
Question::Question(int opposingCandidate, QStringList questionInfo, int seed)
{
    //questionInfo list is set up like this coming from the server:
    //0 "question is blahblahblah?"
    //1 "Clinton's ans"
    //2 "Cruz's ans"
    //3 "Kasich's ans"
    //4 "Sanders's ans"
    //5 "Trump's ans"
    //6 "wildcard ans"
    questionString = questionInfo[0];
    //qDebug() << questionInfo;
    questionInfo.removeFirst();
    setCorrectAnswer(opposingCandidate, questionInfo, seed);

}

/**
 * Sets the correct answer and answer string for the set answers function to use.
 * Calls the setAnswers function.
 * @brief question::setCorrectAnswer
 * @param candidateToMatch
 * @param answerList
 */
void Question::setCorrectAnswer(int candidateToMatch, QList<QString> answerList, int seed)
{
    if(candidateToMatch == 2) //Hillary 2, Clinton 0
        {
            correctAnswer = 0;
            answerString = answerList.at(0);
            answerList.removeAt(0);
        }
        else if (candidateToMatch == 4)//Cruz 4, Cruz 1
        {
            correctAnswer = 1;
            answerString = answerList.at(1);
            answerList.removeAt(1);
        }
        else if(candidateToMatch == 3)//John 3, Kasich 2
        {
            correctAnswer = 2;
            answerString = answerList.at(2);
            answerList.removeAt(2);
        }
        else if(candidateToMatch == 0)//Bernie 0, Sanders 3
        {
            correctAnswer = 3;
            answerString = answerList.at(3);
            answerList.removeAt(3);
        }
        else if(candidateToMatch == 1)// Donald 1, Trump 4
        {
            correctAnswer = 4;
            answerString = answerList.at(4);
            answerList.removeAt(4);
        }
        setAnswers(answerList, seed);
}

/**
 * Sets the answers QList and re-sets the correctAnswer index.
 * @brief question::setAnswers
 * @param oldList
 */
void Question::setAnswers(QList<QString> oldList, int seed)
{
    //create seed
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec() * seed);
    int areWeDoneCount = 4;
    int randomNum = qrand() % 4;
    //qDebug() << randomNum << "-----------------------";
    answers << "" << "" << "" << "";

    while(areWeDoneCount > 0)
    {
        //qDebug() << "The randonNum is " << randomNum;
        //qDebug() << oldList.size() << " is the size of the old list.";
        if(areWeDoneCount == 4)
        {
            answers.replace(randomNum, answerString);
            correctAnswer = randomNum;
            areWeDoneCount--;
        }

        randomNum = qrand() % 4; //get a new random number

        if(answers.at(randomNum).compare("") == 0)
        {
            if(randomNum >= oldList.size())
            {
                //qDebug() << oldList.isEmpty();
                answers.replace(randomNum, oldList.last());
                oldList.removeLast();
            }
            else
            {
                answers.replace(randomNum, oldList.at(randomNum));
                oldList.removeAt(randomNum);
            }
            areWeDoneCount--;
        }

        //qDebug() << "The answerList is: " << answers;
    }
}


/**
 * Returns the question.
 * @brief question::getQuestion
 * @return
 */
QString Question::getQuestion()
{
    return questionString;
}

/**
 * Returns the 4 answers.
 * @brief question::getAnswers
 * @return
 */
QList<QString> Question::getAnswers()
{
    return answers;
}

/**
 * Returns the index of the correct answer in the answers list.
 * @brief question::getCorrectAnswer
 * @return
 */
int Question::getCorrectAnswer()
{
    return correctAnswer;
}
