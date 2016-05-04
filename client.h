#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QList>
#include <QStringList>
#include <QTcpSocket>


class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = 0);
    ~Client();
    QString username;
    QString password;
    QString groupID;

private slots:
    void sendNewAccountInfo(QString,QString,QString,QString, bool);
    void loginAccount(QString,QString);
    void getNewQuestion();
    void readyRead();
    void disconnected();
    void decodeMessage(QString);
    void dropoutUser(QString);
    void characterSelected(QString, int);
    void updateScore(QString, int, int);
    void getLeaderBoardWithGroupID(QString);

signals:
    void sendQuestionsToModel(QList<QStringList>);
    void sendAccountInfoToModel(QStringList);
    void returnLeaderBoard(QList<QStringList>, QList<QStringList>);
    void newAccountResultMessage(QString);

private:
    QTcpSocket *client;

};

#endif // CLIENT_H
