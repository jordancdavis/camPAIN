#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <QTcpServer>

class WebServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit WebServer(int portNum = 9998, QObject *parent = 0);
    void startWebServer();

private:
    int portNumber;

protected:
    void incomingConnection(qintptr socketDescriptor);

};

#endif // WEBSERVER_H
