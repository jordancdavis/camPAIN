#include "client.h"
#include <QTcpSocket>
#include <QByteArray>
#include <QHostAddress>

/**
 * @brief Client::Client
 * @param parent
 *
 * Client code came from:
 * http://www.bogotobogo.com/Qt/Qt5_QTcpSocket.php
 */
Client::Client(QObject *parent) :
    QObject(parent)
{
    client = new QTcpSocket();

    connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));

    client->connectToHost(QHostAddress::LocalHost, 9999);

    //connect(client, SIGNAL(sendAccountInfo(QString, QString)), this, SLOT(sendAccountInfo(QString,QString)));
}

/**
 * Server destructor to get rid of pointers.
 */
Client::~Client() {
    delete client;
}

/**
 * This is a slot that will be called when the Sign up button on the GUI is clicked.
 * This extracts the username and password and gives it to the server for entry in the
 * database.
 * @brief Client::sendNewAccountInfo
 * @param usr
 * @param psswrd
 * @param group
 * @param groupPsswrd
 * @param isAdmin
 */
void Client::sendNewAccountInfo(QString usr, QString psswrd, QString group, QString groupPsswrd, bool isAdmin)//, Server server)
{
    username = usr;
    password = psswrd;
    groupID = group;

    // connects to our server
//    client->connectToHost(QHostAddress::LocalHost, 9999);

    QString admin;
    if (isAdmin)
        admin = "1";
    else
        admin = "0";

    std::string accountInfoMessage = "NA\n" + username.toStdString() + "\n" + password.toStdString() + "\n" +
            group.toStdString() + "\n" + groupPsswrd.toStdString() + "\n" + admin.toStdString();

    // This should send the new account info to the server
    client->write(accountInfoMessage.c_str());
}

/**
 * @brief Client::loginAccount - slot for logging in a user. Sends
 * info to server to check for correctness.
 * @param usr - username for user trying to log in
 * @param pword - password for user trying to log in
 */
void Client::loginAccount(QString usr, QString pword)
{
    username = usr;
    password = pword;

//    client->connectToHost(QHostAddress::LocalHost, 9999);

    std::string accountInfoMessage = "RA\n" + username.toStdString() + "\n" + password.toStdString();

    client->write(accountInfoMessage.c_str());
}

/**
 * This is a slot in the client class.
 * This method is called when data from the server has come accross to the client.
 * @brief Client::readyRead
 */
void Client::readyRead()
{
    // read all data from socket
    QByteArray data = client->readAll();

    QString strData = QString::fromStdString(data.toStdString());

    decodeMessage(strData);
    // will write on client side window
}

/**
 * @brief Server::disconnected
 * This is another slot that is called when the server is finshed sending data
 * to the client. It closes the connection between the client and server.
 */
void Client::disconnected()
{
    qDebug() << "disconnected client";
    client->close();
}


/**
 * @brief Client::getNewQuestion is used to acquire a question from the database based off the QID.
 * @param QID
 */
void Client::getNewQuestion()
{
//    qDebug() << "in new question";
//    client->connectToHost(QHostAddress::LocalHost, 9999);

    std::string questionQuery = "Q\n";

    client->write(questionQuery.c_str());
}

/**
 * @brief Client::decodeMessage - receives a message from the server
 * and decodes it to send back to the game
 * @param message - the message received from the server
 */
void Client::decodeMessage(QString message)
{
    QStringList queryList;
    QString result;
    QString typeOfQuery;

    QStringList queryList1;
    QStringList queryList2;
    bool leaderboard = false;

    if (message.startsWith("LB"))
    {
        QStringList lbs = message.split(QRegExp("[\r]"));
        queryList1 = lbs.at(1).split(QRegExp("[\n]"));
        queryList2 = lbs.at(2).split(QRegExp("[\n]"));
        leaderboard = true;
    }
    else
    {
        queryList = message.split(QRegExp("[\n]"));
        typeOfQuery = queryList.at(0);
    }

    // code to get a Question out of the database
    if(typeOfQuery == "Q")
    {
        // This list will contain a list of Qstrings at each position
        QList<QStringList> questions;
        QStringList temp;
        // The questions needed are in positions 1-5 of queryList
        for(unsigned int i = 1; i < 6; i++)
        {
            // This will take the question/answers from queryList and split each component based off tabs.
            temp = queryList.at(i).split(QRegExp("[\t]"));
            questions.append(temp);
        }

        //emit signal to give QList<QStringList> to model
        emit sendQuestionsToModel(questions);
        // get the question and throw it into a QList<QList<QString>> questions;
        // take each questions and separate them by tabs that will go into the overall QList
        // take 1-5 indexes then we split by tabs.
    }
    // code to Retrieve Account info from database
    else if(typeOfQuery == "RA")
    {
        // Remove RA from the list
        queryList.removeFirst();
        //qDebug() << queryList;
        // Send the list to the model
        emit sendAccountInfoToModel(queryList);
    }
    else if (typeOfQuery == "NA")
    {
        emit newAccountResultMessage(queryList[1]);
    }
    // code to get Leaderboard from database
    else if (leaderboard)
    {
        QList<QStringList> leaderboardGlobal;
        QList<QStringList> leaderboardGroup;
        QStringList user;

        // Split the user information on tab and append to string list
        // then add that string list to the list of stringlists.
        for(unsigned int i = 0; i < queryList1.size(); i++)
        {
            user = queryList1.at(i).split(QRegExp("[\t]"));
            leaderboardGlobal.append(user);
        }

        for (unsigned int i = 0; i <queryList2.size(); i++)
        {
            user = queryList2.at(i).split(QRegExp("[\t]"));
            leaderboardGroup.append(user);
        }

        // Send leaderboard back to the model
        emit returnLeaderBoard(leaderboardGlobal, leaderboardGroup);
    }
}

/**
 * @brief Client::dropoutUser - reset user info
 * @param username
 */
void Client::dropoutUser(QString username)
{
    //do the dropout stuff, reset all game settings
    QString dropout = "DO\n" + username;
    // Send message to server
    client->write(dropout.toStdString().c_str());
}

/**
 * @brief Client::characterSelected - send character select info to server
 * @param username - current user
 * @param candidate - which candidate they selected (int encoding)
 */
void Client::characterSelected(QString username, int candidate)
{
    //save character
    QString message = "UC\n" + username + "\n" + QString::number(candidate);
    client->write(message.toStdString().c_str());
}

/**
 * @brief Client::updateScore - update the player's score in the DB after
 * a debate
 * @param username - user whose score needs to be updated
 * @param votes - the new score
 * @param candidateDefeated - who they debated with (int encoding)
 */
void Client::updateScore(QString username, int votes, int candidateDefeated)
{
    //updates votes and candidates defeated. (CandidateDefeated is -1 if none defeated)
    QString defCand;
        // Determine which candidate was fought based on character encoding
        if (candidateDefeated == 0)
            defCand = "defBern";

        else if(candidateDefeated == 1)
            defCand = "defTrump";

        else if(candidateDefeated == 2)
            defCand = "defHill";

        else if(candidateDefeated == 3)
            defCand = "defKas";

        else if(candidateDefeated == 4)
            defCand = "defCruz";

        // Send message to server
        QString message = "US\n" + username + "\n" + QString::number(votes) + "\n" + defCand;
        client->write(message.toStdString().c_str());
}

/**
 * @brief Client::getLeaderBoardWithGroupID - get leaderboard from server - either a
 * leaderboard of top ten players or all players from the given group
 * @param groupID - if the groupid is null or empty - no group specified -
 * get top ten players of all time. otherwise send the group id to get all
 * players in that group
 */
void Client::getLeaderBoardWithGroupID(QString groupID)
{
    QString message = "LB\n" + groupID;
    client->write(message.toStdString().c_str());
}


