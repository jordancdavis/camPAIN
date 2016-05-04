#ifndef DBSERVER_H
#define DBSERVER_H

#include <mysql.h>
#include <QString>
#include <QList>

class DBServer
{
public:
    DBServer();
    ~DBServer();
    // Returns a map of answers to the given question specified by the int QID
    QList<QString> getNextQuestion(int);
    // Record player progress with the given login, current # of votes, player defeated
    void recordProgress(QString, QString, QString);
    // Check if the player entered correct info for log in with given login and password
    QList<QString> checkPlayer(QString, QString);
    // Register a new player with given login, password, group, group password, and admin bool
    QString newPlayer(QString, QString, QString, QString, QString);
    // Get the leaderboard with the given groupID - or all time with an empty string
    QList<QList<QString> > getLeaderboard(QString);
    // Set the user's selected candidate based on int value
    void characterSelect(QString, QString);
    // Droupout (reset score) given user
    void dropout(QString);
    // Check if the give login is available
    bool checkUniqueLogin(QString);
    bool loginAndPasswordCorrect(QString, QString);
    bool checkUniqueGroup(QString);
    bool checkIfUserIsAdmin(QString);
    // Helper method to return player info
    QList<QString> getUserInfo(QString);
    // deletes given account from database if it exists
    bool deleteAccount(QString);

private:
    // keeps the result taken from the sql server query
    MYSQL_RES *result;
    // contains selected rows from the result
    MYSQL_ROW row;
    /*
     * mysql: the mysql object that communicates with the server
     * connection: The actual TCP/IP connection to the mySQL server
     */
    MYSQL *connection, mysql;
    // Determines if queries were successful (0)
    int state;
    // Helper method to check high score when player info is updated
    void updateHighScore(QString, QString);
};

#endif // DBSERVER_H

