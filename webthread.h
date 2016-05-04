#ifndef WEBTHREAD_H
#define WEBTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include "dbserver.h"

class WebThread : public QThread
{
    Q_OBJECT
public:
    explicit WebThread(qintptr, QObject *parent = 0);

    // when thread starts, this method is called.
    void run();

signals:
    // when thread does not work, it will send a socket error through the given socket
    void error(QTcpSocket::SocketError socketerror);

public slots:
    // When the server gets a request from a client, the data is sent to this method.
    void readyRead();
    // When the server gets a message that the client has disconnected, this method will be called.
    void disconnected();

private:
    // Socket used to listen on and communicate with outside clients
    QTcpSocket *socket;
    qintptr socketDescriptor;
    QString *filePath;

    QString acknowledgmentMessage = "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Type: text/html; charset=UTF-8\r\n";

    // Allows access to the database
    DBServer *database;

    // this method will send an appropriate HTML message to the web client
    void sendHTML(QString);

    // Takes the QString given and decodes what the page is asking.
    QString decodeHTMLMessage(QString);

    // Returns a sendable string for the front page of the CamPAIN analytics webpage.
    void getFrontPage(QString*);

    // Returns a sendable string with the leaderboard content for the given group.
    void getLeaderboard(QString, QString*);

    //Returns a sendable string for that particular user's accompishments
    void getUser(QString, QString*);

    void deleteAccount(QString&, QString*);

    void getLeaderboardHTML(QString, QString, QString*);

};

#endif // WEBTHREAD_H

