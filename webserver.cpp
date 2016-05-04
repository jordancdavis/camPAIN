/*
 * Written by Mackenzie Elliot and William Nathan Merrill
 */

#include "webserver.h"
#include "webthread.h"

WebServer::WebServer(int portNum, QObject *parent) :
    QTcpServer(parent), portNumber(portNum) {}


void WebServer::startWebServer()
{
    if(!this->listen(QHostAddress::LocalHost, portNumber))
    {
        qDebug() << "QWebServer could not start";
    }
    else
    {
        qDebug() << "Web Server started, listening on port " << portNumber;
    }
}

void WebServer::incomingConnection(qintptr socketDescriptor)
{

   // create a new thread for the webserver to be maintained.
   WebThread *thread = new WebThread(socketDescriptor, this);

   // connect signal/slot
   // once a thread is not needed, it will be beleted later
   connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

   thread->start();
}
