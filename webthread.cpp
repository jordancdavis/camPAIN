/*
 * Written by Karla Kraiss and William Nathan Merrill
 */

#include <QFile>
#include <QTextStream>
#include "webthread.h"

/**
 * @brief WebThread::WebThread
 * @param ID
 * @param parent
 */
WebThread::WebThread(qintptr ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
    filePath = new QString("./Resources/HTMLFrontPage");
}

/**
 * @brief WebThread::run
 */
void WebThread::run()
{
    qDebug() << "Web Thread started";
    database = new DBServer();

    socket = new QTcpSocket();

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

    // Send web page that we acknowledge them
    socket->write(acknowledgmentMessage.toStdString().c_str());
    socket->write("\r\n");

    exec();
}

/**
 * @brief WebThread::readyRead
 */
void WebThread::readyRead()
{
    QByteArray data = socket->readAll();

    // convert message to QString to be split
    QString strData = QString::fromStdString(data.toStdString());

    // split the message correctly
    QStringList queryList = strData.split(QRegExp("[\r\n]"));

    // Grabing the GET message specifically
    sendHTML(queryList[0]);
}

/**
 * @brief WebThread::disconnected
 */
void WebThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
}

/**
 * @brief WebThread::sendHTML
 * @param webQuery
 */
void WebThread::sendHTML(QString webQuery)
{
    QString html = decodeHTMLMessage(webQuery);
    socket->write(html.toStdString().c_str());
    socket->close();
}

/**
 * @brief WebThread::decodeHTMLMessage
 * @param message
 * @return
 */
QString WebThread::decodeHTMLMessage(QString message)
{
    // html page to be passed through methods and added to based on criteria.
    QString *htmlPage = new QString("<!DOCTYPE html><html lang=\"en\" xmlns=\"http://www.w3.org/1999/xhtml\">"
                                    "<head><meta charset=\"utf-8\"/>"
                                    "<title></title>"
                                    "</head><body>");
    // Admin login
    if(message.contains("?adminName=") && message.contains("password="))
    {
        getLeaderboard(message, htmlPage);
    }
    // link to specific user
    else if(message.contains("?username=")){
        getUser(message, htmlPage);
    }
    else if(message.contains("?deleteAccount="))
    {
        deleteAccount(message, htmlPage);
    }
    // if neither of the above are in the URL, it should be on the front page
    else
    {
        getFrontPage(htmlPage);
    }

    htmlPage->append("</body></html>");
    return *htmlPage;
}

/**
 * @brief WebThread::getFrontPage
 * @param htmlFrontPage
 */
void WebThread::getFrontPage(QString *htmlFrontPage)
{
    htmlFrontPage->append("<h1><center>Welcome to the <font color=\"red\"> CamPAIN </font> front page</center></h1>"
                            "<form action=\"http://localhost:9998/\" method=\"get\"> <center>"
                            "<input type=\"text\" name=\"adminName\" placeholder=\"Admin UserName\">"
                            "<input type=\"password\" size=\"25\" name=\"password\" placeholder=\"Admin Password\">"
                            "<button>Get Leaderboard</button>"
                            "</center></form>");
}

/**
 * @brief WebThread::getLeaderboard
 * @param message
 * @param htmlLeaderboardPage
 */
void WebThread::getLeaderboard(QString message, QString *htmlLeaderboardPage)
{
    QStringList splitMessage =  message.split(QRegExp("[/?= &]"));
    // this position of the message will contain the admin user name
    QString adminName = splitMessage.at(4);
    // ""       ""   ""  ""    ""    ""    ""     ""  ""   password
    QString adminPass = splitMessage.at(6);

    // make sure the username and password are at least correct
    if(database->loginAndPasswordCorrect(adminName, adminPass))
    {
        // double check that the user is an admin
        if(database->checkIfUserIsAdmin(adminName))
        {
            getLeaderboardHTML(adminName, adminPass, htmlLeaderboardPage);
        }
        else
        {
            htmlLeaderboardPage->append("<h1><center>Welcome to the <font color=\"red\"> CamPAIN </font> front page</center></h1>"
                                               "<h1><center> Username is not an Admin</center></h1>"
                                               "<form action=\"http://localhost:9998/\" method=\"get\"> <center>"
                                               "<input type=\"text\" name=\"adminName\" placeholder=\"Admin UserName\">"
                                               "<input type=\"password\" size=\"25\" name=\"password\" placeholder=\"Admin Password\">"
                                               "<button>Get Leaderboard</button>"
                                               "</center></form>");
        }
    }
    else
    {
        htmlLeaderboardPage->append("<h1><center>Welcome to the <font color=\"red\"> CamPAIN </font> front page</center></h1>"
                                           "<h1><center> Incorrect username or password</center></h1>"
                                           "<form action=\"http://localhost:9998/\" method=\"get\"> <center>"
                                           "<input type=\"text\" name=\"adminName\" placeholder=\"Admin UserName\">"
                                           "<input type=\"password\" size=\"25\" name=\"password\" placeholder=\"Admin Password\">"
                                           "<button>Get Leaderboard</button>"
                                           "</center></form>");
    }
}

/**
 * @brief WebThread::getUser
 * @param message
 * @param htmlUserPage
 */
void WebThread::getUser(QString message, QString* htmlUserPage){
    QStringList splitMessage =  message.split(QRegExp("[/?= &]"));

    // contain all the username and admin info for use in the html link
    QString userName = splitMessage.at(4);
    QString adminName = splitMessage.at(6);
    QString adminPass = splitMessage.at(8);

    // creates html page syntax and semantics
    htmlUserPage->append("<style>tr:hover{background-color: #A5B1B5}</style></head><h1><center>" + userName + "'s Progress</center></h1><center>"
                                                     "<p><a href=\"http://localhost:9998/?adminName=" + adminName +
                                                     "&password=" + adminPass + "\">Back to Leaderboard</a></p></center><table border =\"1\", "
                                                     "style =\"width:100%\"><tr bgcolor=\"#E0FFFF\", style=\"font-weight:bold\">"
                                                     "<td><center>Highscore</center></td><td><center>Votes</center></td><td><center>Candidate"
                                                     "</center></td><td><center>Defeated Clinton</center></td><td><center>Defeated Cruz"
                                                     "</center></td><td><center>Defeated Kasich</center></td><td><center>Defeated Sanders"
                                                     "</center></td><td><center>Defeated Trump</center></td></tr><tr bg=\"#E6E6FA\">");

    // get user info
    QList< QString > tableData = database->getUserInfo(userName);

    // loop through tableData and append the user info
    for(int i = 1; i < tableData.length() - 1; i++)
    {
        if(i == 3){
            switch ( tableData[i].toInt() ){
            case 0:
                htmlUserPage->append("<td><center>Bernie Sanders</center></td>");
                break;
            case 1:
                htmlUserPage->append("<td><center>Donald Trump</center></td>");
                break;
            case 2:
                htmlUserPage->append("<td><center>Hillary Clinton</center></td>");
                break;
            case 3:
                htmlUserPage->append("<td><center>John Kasich</center></td>");
                break;
            case 4:
                htmlUserPage->append("<td><center>Ted Cruz</center></td>");
                break;
            default:
                htmlUserPage->append("<td><center>No Candidate</center></td>");
                break;
            }
        }
        else if(tableData[i] == "1"){
             htmlUserPage->append("<td><center>yes</center></td>");
        }
        else if(tableData[i] == "0"){
             htmlUserPage->append("<td><center>no</center></td>");
        }
        else{
            htmlUserPage->append("<td><center>" + tableData[i] + "</center></td>");
        }
    }

    htmlUserPage->append("</tr>");
}


void WebThread::deleteAccount(QString& message, QString* htmlPage)
{
    QStringList splitMessage =  message.split(QRegExp("[/?= &]"));
    QString account = splitMessage[4];
    QString admin = splitMessage[6];
    QString adminPass = splitMessage[8];

    if(database->deleteAccount(account))
    {
        wait(1);
        qDebug() << "about to get Leaderboard again";
        getLeaderboardHTML(admin, adminPass, htmlPage);
    }
    else
    {
        getFrontPage(htmlPage);
        htmlPage->append("<h1><center>Problem connecting to Database</center></h1>");
    }
}

void WebThread::getLeaderboardHTML(QString adminName, QString adminPass, QString *htmlLeaderboardPage)
{
    QString groupID = database->getUserInfo(adminName).at(9);

    htmlLeaderboardPage->append("<style>tr:hover{background-color: #A5B1B5}</style></head> <body><h1><center>" + adminName +
                             "'s Class</center></h1><center><p><a href=\"http://localhost:9998/\">Log Out</a></p></center>"
                             "<table border =\"1\", style =\"width:100%\"><tr bgcolor=\"#E0FFFF\", style=\"font-weight:bold\">"
                             "<td><center>login</center></td><td><center>highscore</center></td></tr>");

    QList<QList<QString> > tableData = database->getLeaderboard(groupID);
    for(QList<QString> row : tableData)
    {
        htmlLeaderboardPage->append("<tr bg=\"#E6E6FA\"><td><center><a href=http://localhost:9998/?username=" + row[0] +
                "&adminName=" + adminName + "&password=" + adminPass + ">" +
                row[0] + "</a></center></td><td><center>" + row[1] + "</center></td>"
                                                                     "<td width=25>"
                                                                     "<a href=http://localhost:9998/?deleteAccount="+ row[0] + "/admin="+adminName+"&adminPass="+adminPass+">"
                                                                      " Delete Account"
                                                                      "</td></tr>");
    }
}

