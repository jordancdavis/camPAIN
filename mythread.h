#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include "dbserver.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(qintptr ID, QObject *parent = 0);

    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;

    DBServer *database;

    void queryDatabase(QString);

    QString getSetOfQuestions();
    QString getLeaderboard(QString);
    QString getInfo(QList<QString>);
    QList<int>* randNumGen();
    const int sizeOfQuestionTable = 45;
};

#endif // MYTHREAD_H

