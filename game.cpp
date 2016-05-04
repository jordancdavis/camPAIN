#include "game.h"
#include <QObject>
#include <QDebug>

Game::Game(QObject *parent) : QObject(parent)
{
    votes = 0;
    myCandidate = -1;
    opposingCandidate = -1;
    groupID = "";
    candidatesDefeated = QList<bool>();
    candidatesDefeated.push_back(false);
    candidatesDefeated.push_back(false);
    candidatesDefeated.push_back(false);
    candidatesDefeated.push_back(false);
    candidatesDefeated.push_back(false);
}

void Game::setLevelOrder()
{
   levelOrder = QList<int>();

   if(myCandidate == 0) //Bernie
   {
       levelOrder.push_back(0); //Bernie
       levelOrder.push_back(2); //Hillary
       levelOrder.push_back(3); //John
       levelOrder.push_back(4); //Ted
       levelOrder.push_back(1); //Donald
   }
   else if(myCandidate == 1) //Donald
   {
       levelOrder.push_back(1); //Donald
       levelOrder.push_back(3); //John
       levelOrder.push_back(4); //Ted
       levelOrder.push_back(0); //Bernie
       levelOrder.push_back(2); //Hillary
   }
   else if(myCandidate == 2) //Hillary
   {
       levelOrder.push_back(2); //Hillary
       levelOrder.push_back(0); //Bernie
       levelOrder.push_back(3); //John
       levelOrder.push_back(4); //Ted
       levelOrder.push_back(1); //Donald
   }
   else if(myCandidate == 3) //John
   {
       levelOrder.push_back(3); //John
       levelOrder.push_back(4); //Ted
       levelOrder.push_back(1); //Donald
       levelOrder.push_back(0); //Bernie
       levelOrder.push_back(2); //Hillary
   }
   else if(myCandidate == 4) //Ted
   {
       levelOrder.push_back(4); //Ted
       levelOrder.push_back(3); //John
       levelOrder.push_back(1); //Donald
       levelOrder.push_back(0); //Bernie
       levelOrder.push_back(2); //Hillary
   }
}

void Game::setCharacter(int characterNumber)
{
    myCandidate = characterNumber;
    setLevelOrder();
    emit sendCharacterSelectionToDB(playerUsername, characterNumber);
}

void Game::getStageList()
{
    setLevelOrder();
    emit returnStageList(levelOrder, candidatesDefeated);
    emit setVotes(votes);
}

void Game::playerDroppedOut(){
    emit dropoutWithUsername(playerUsername);
    myCandidate = -1;
    opposingCandidate = -1;
    votes = 0;
    emit setVotes(votes);
    candidatesDefeated = QList<bool>();
    candidatesDefeated.push_back(false);
    candidatesDefeated.push_back(false);
    candidatesDefeated.push_back(false);
    candidatesDefeated.push_back(false);
    candidatesDefeated.push_back(false);
    emit resetStageColors();
}

void Game::updateOpponent(int opponentIndex)
{
    opposingCandidate = levelOrder[opponentIndex];
}

/**
 * @brief level::checkAnswer
 * @param answer
 *
 * A method that checks the accuracy of the user's answer
 * against our own, correct, answer.
 */
void Game::checkAnswer(int answer) {
    if(answer == correctAnswer) {
        emit checkedAnswer(true, correctAnswer);
        correctCount++;
    }
    else {
        emit checkedAnswer(false, correctAnswer);
    }
    currentLevelStatus();
}

/**
 * @brief level::currentLevelStatus
 *
 * Determines the status of the level/determines if the level has
 * been completed and won.
 */
void Game::currentLevelStatus() {
    currentQuestion++;
    if(currentQuestion > 5) {
        if(correctCount >= 3) {
            emit winLevel(correctCount);
        }
        else {
            emit loseLevel(correctCount);
        }
        currentQuestion = 0;
        correctCount = 0;
    }
}

void Game::getQuestions() //move this to client
{
    QList<QStringList> questions;

    //questionInfo list is set up like this coming from the server:
        //0 "question is blahblahblah?"
        //1 "Clinton's ans"
        //2 "Cruz's ans"
        //3 "Kasich's ans"
        //4 "Sanders's ans"
        //5 "Trump's ans"
        //6 "wildcard ans"
    QStringList list1;
    list1 << "What is my slogan?" << "Hillary for America" << "Reigniting the Promise of America" << "K for US" << "A political revolution is coming" << "Make america great again!" << "Land of the free, home of the brave!";

    QStringList list2;
    list2 << "What is my 2nd question?" << "Hillary1" << "Cruz1" << "Kasich1" << "Bernie1" << "Trump1" << "Wildcard1";

    QStringList list3;
    list3 << "What is my 3rd question?" << "Hillary2" << "Cruz2" << "Kasich2" << "Bernie2" << "Trump2" << "Wildcard2";

    QStringList list4;
    list4 << "What is my 4th question?" << "Hillary3" << "Cruz3" << "Kasich3" << "Bernie3" << "Trump3" << "Wildcard3";
    QStringList list5;
    list5 << "What is my 5th question?" << "Hillary4" << "Cruz4" << "Kasich4" << "Bernie4" << "Trump4" << "Wildcard4";

    questions << list1 << list2 << list3 << list4 << list5;

    returnQuestionsFromDB(questions);
}

void Game::receiveQuestionFromDB(QList<QStringList> questionLists)
{
    QList<Question> questionObjects = QList<Question>();
    int random = 349;
    for(QStringList & questionList : questionLists)
    {
        Question q = Question(opposingCandidate, questionList, random);
        questionObjects.append(q);
        random += 13;
    }
    emit returnQuestions(questionObjects);
}

void Game::receiveGameInfo(QStringList loginInfo)
{
    playerUsername = loginInfo[0];

    setCharacter(loginInfo[3].toInt()); //parse string to int?
    if(loginInfo[4].compare("1") == 0)//hillary
    {
        candidatesDefeated[2] = true;
    } else {
        candidatesDefeated[2] = false;
    }
    if(loginInfo[5].compare("1") == 0)//cruz
    {
        candidatesDefeated[4] = true;
    } else {
        candidatesDefeated[4] = false;
    }
    if(loginInfo[6].compare("1") == 0)//kasich
    {
        candidatesDefeated[3] = true;
    } else {
        candidatesDefeated[3] = false;
    }
    if(loginInfo[7].compare("1") == 0)//bernie
    {
        candidatesDefeated[0] = true;
    } else {
        candidatesDefeated[0] = false;
    }
    if(loginInfo[8].compare("1") == 0)//trump
    {
        candidatesDefeated[1] = true;
    } else {
        candidatesDefeated[1] = false;
    }
    emit resetStageColors();
}

void Game::candidateDefeated(int numVotes)
{
    votes = numVotes;
    emit setVotes(votes);
    candidatesDefeated.removeAt(opposingCandidate);
    candidatesDefeated.insert(opposingCandidate, true);
    emit returnStageList(levelOrder, candidatesDefeated);
    emit sendScoreToDB(playerUsername, votes, opposingCandidate);
}

void Game::getLeaderBoardFromDB()
{
    emit getLeaderBoardWithGroupID(groupID);
}
