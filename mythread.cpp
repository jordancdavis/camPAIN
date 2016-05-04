/*
 * Written by Mackenzie Elliot, Isabelle (Boo) Chaloub, William Nathan Merrill
 */

#include "mythread.h"
#include <iostream>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include <QBuffer>
#include <QString>
#include <QTextCodec>
#include <QtGlobal>
#include <QDateTime>
#include <QDebug>


MyThread::MyThread(qintptr ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
}

void MyThread::run()
{
    database = new DBServer();
    // thread starts here

    socket = new QTcpSocket();

    // set new seed for rng
    qsrand( QDateTime::currentDateTime().toTime_t());

    // set the ID
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // We'll have multiple clients, we want to know which is which
    qDebug() << socketDescriptor << " Client connected";

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies

    exec();
}

/**
 * @brief Server::readyRead
 * This is another slot that is called from the QTcpSocket that will
 * extract data from the client socket when it has come across the network.
 * The data is read into a Byte array which can then be parsed and given to the
 * Database Server. The Byte array MUST contain all the necessary information and the contents
 * seperated by new lines "\n".
 */
void MyThread::readyRead()
{
    QByteArray data = socket->readAll();

    QString strData = QString::fromStdString(data.toStdString());
    if(strData.length() > 0)
    {
        queryDatabase(strData);
    }
}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
}

/**
 * @brief Server::queryDatabase This method will determine what to query from the database based on the
 * client query given.
 * @param clientQuery
 * @return
 */
void MyThread::queryDatabase(QString clientQuery)
{
    QStringList queryList = clientQuery.split(QRegExp("[\n]"));
    QString result;

    QString typeOfQuery = queryList.at(0);

    // code to enter New Account into database
    if(typeOfQuery == "NA")
    {
        qDebug() << "In NA";
        if (queryList.size() < 5)
            qDebug() << "bad list";

        result = "NA\n" + database->newPlayer(queryList.at(1), queryList.at(2), queryList.at(3), queryList.at(4), queryList.at(5));
    }
    // code to get a Question out of the database
    else if(typeOfQuery == "Q")
    {
        result = "Q\n" + getSetOfQuestions();
    }
    // code to Retrieve Account info from database
    else if(typeOfQuery == "RA")
    {
        result = "RA\n" + getInfo(database->checkPlayer(queryList.at(1), queryList.at(2)));
    }
    // code to dropout a player from database
    else if(typeOfQuery == "DO")
    {
        database->dropout(queryList.at(1));
    }
    // code to Update Score in database
    else if(typeOfQuery == "US")
    {
        database->recordProgress(queryList.at(1), queryList.at(2), queryList.at(3));
    }
    // code to Update the current Candidate chosen by the account
    else if(typeOfQuery == "UC")
    {
        database->characterSelect(queryList.at(1), queryList.at(2));
    }
    // code to get the leaderboard
    else if(typeOfQuery == "LB")
    {
        result = "LB\r" + getLeaderboard(queryList.at(1));
    }
    socket->write(result.toStdString().c_str());
}

/**
 * @brief MyThread::randNumGen - Returns a list of 5 random numbers
 * @return
 */
QList<int>* MyThread::randNumGen()
{
   QList<int> *numbers = new QList<int>();
   int n;
   for(int i = 0; i < 5; i++)
   {
       n = (qrand() % sizeOfQuestionTable) + 1;
       while(numbers->contains(n))
       {
            n = qrand() * 7 % sizeOfQuestionTable + 1;
       }
       numbers->append(qAbs(n));
   }
   return numbers;
}

/**
 * @brief Server::getSetOfQuestions will return a string that is able to be sent to client
 * @return
 */
QString MyThread::getSetOfQuestions()
{
   QList<QList<QString> > setOfQuestions;
   QString mail = "";
   QList<int> *numList = randNumGen();

   for(int i = 0; i < 5; i ++)
   {
      setOfQuestions.append( database->getNextQuestion( numList->at(i)) );
   }

   for(QList<QString> questionSet : setOfQuestions)
   {
       for(QString s : questionSet)
       {
          mail += s;
          if(!questionSet.endsWith(s))
          {
             mail += "\t";
          }
       }

       if(!setOfQuestions.endsWith(questionSet))
       {
           mail += "\n";
       }
   }

   return mail;
}

/**
 * @brief MyThread::getLeaderboard - gets ,ap of leaderboard information from DB
 * and converts it to a string to be sent back to the client
 * @param group - group name
 * @return String message of the converted leaderboard information
 */
QString MyThread::getLeaderboard(QString group)
{
    QList<QList<QString> > leaderboard1 = database->getLeaderboard("null");
    QString mail = "";
    for(QList<QString> user : leaderboard1)
    {
        for(QString item : user)
        {
           mail += item;
           if(!user.endsWith(item))
           {
              mail += "\t";
           }
        }

        if(!leaderboard1.endsWith(user))
        {
            mail += "\n";
        }
    }

    mail += "\r";
    QList<QList<QString> > leaderboard2 = database->getLeaderboard(group);

    for(QList<QString> user : leaderboard2)
    {
        for(QString item : user)
        {
           mail += item;
           if(!user.endsWith(item))
           {
              mail += "\t";
           }
        }

        if(!leaderboard2.endsWith(user))
        {
            mail += "\n";
        }
    }
    return mail;
}

/**
 * @brief MyThread::getInfo - converts user info list
 * into a string to be sent back to client
 * @param info - list of user info from DB
 * @return string message for the client
 */
QString MyThread::getInfo(QList<QString> info)
{
    QString mail = "";
    for (QString s : info)
    {
        mail += s;
        if (!info.endsWith(s))
            mail += "\n";
    }
    return mail;
}



