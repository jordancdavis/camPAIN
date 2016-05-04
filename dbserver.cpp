/*
 * Written by Mackenzie Elliott, Isabelle (Boo) Chaloub, and William Nathan Merrill
 */

#include "dbserver.h"
#include <iostream>
#include <QDebug>

/**
 * @brief DBServer::DBServer - Database Constructor - sets up connection
 */
DBServer::DBServer()
{
    mysql_init(&mysql);

    connection = mysql_real_connect(&mysql, "128.110.68.243", "root", "campain", "CamPAINdb", 3306, 0, 0);

    if (connection == NULL)
    {
        std::cout << mysql_error(&mysql) << std::endl;
    }
}

/**
 * @brief DBServer::~DBServer - Database destructor - closes connection
 */
DBServer::~DBServer()
{
    mysql_close(connection);
}

/**
 * @brief DBServer::getNextQuestion - queries the database for the question
 * and answers with the given QID
 * @param qid - ID for which question to get from database
 * @return - A list of strings, the question being in the first spot and all
 * the answers after it.
 */
QList<QString> DBServer::getNextQuestion(int qid)
{
    QString query = "SELECT * FROM Questions WHERE QID = " + QString::number(qid) + ";";
    state = mysql_query(connection, query.toStdString().c_str());

    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
    }

    result = mysql_store_result(connection);

    row = mysql_fetch_row(result);

    QList<QString> question;

    for(int i = 0; i < result->field_count-1; i++)
    {
        question.append(row[i+1]);
    }

    return question;
}

/**
 * @brief DBServer::recordProgress - updates a user's score in the database
 * @param login - the user whose score is being updated
 * @param score - their score for that debate
 * @param defCand - which candidate they fought against
 * @param win - 0 if they lost or a 1 if they won
 */
void DBServer::recordProgress(QString login, QString score, QString defCand)
{
    // Send updated info to the DB
    QString query = "UPDATE Users SET votes = " + score + ", " + defCand + " = 1 WHERE login = '" + login + "';";

    state = mysql_query(connection, query.toStdString().c_str());

    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
    }

    // Call helper method to add to high score
    updateHighScore(login, score);
}

/**
 * @brief DBServer::updateHighScore - Helper method to update the high score when
 * the user finishes a debate.
 * @param login - the user whose score is being updated
 * @param newScore - the new score that needs to be added to their high score
 */
void DBServer::updateHighScore(QString login, QString newScore)
{
    qDebug() << "highscoring...";
    // Get the player's current high score
    QString query = "SELECT highScore FROM Users WHERE login = '" + login + "';";

    state = mysql_query(connection, query.toStdString().c_str());

    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
    }

    result = mysql_store_result(connection);

    row = mysql_fetch_row(result);
    QString highScore = row[0];

    // Takes the current high score and then updates it by adding the new score.
    int currHighScore = highScore.toInt() + newScore.toInt();

    // Update DB with new high score
    query = "UPDATE Users SET highScore = " + QString::number(currHighScore) + " WHERE login = '" + login + "';";

    state = mysql_query(connection, query.toStdString().c_str());
    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
    }
    qDebug() << "successful highscore";
}

/**
 * @brief DBServer::checkPlayer - called when logging in a user. checks if the name exists
 * and if so, if the password is correct. If the login is successful, returns all of their game
 * info from their previous login to continue game where they left off.
 * @param login - attempted login
 * @param password - attempted password for login
 * @return - a list that either holds all of the user's info or an error message inside the list
 * giving a reason for failed log in.
 */
QList<QString> DBServer::checkPlayer(QString login, QString password)
{
    QList<QString> info;
    QString error;

    // If true - login doesn't exist - send error in list
    if (checkUniqueLogin(login))
    {
        error = "Username does not exist.";
        info.append(error);
        return info;
    }

    // See if the password matches the login
   if(!loginAndPasswordCorrect(login, password))
   {
        error = "Password incorrect.";
        info.append(error);
        return info;
    }
    // Otherwise - info was good - call helper method to get their user info to send back
    else
        return getUserInfo(login);
}

/**
 * @brief DBServer::checkUniqueLogin - checks if the given username exists in the DB
 * @param login - username that the new user wants to use
 * @return true if the username is unique. false otherwise
 */
bool DBServer::checkUniqueLogin(QString login)
{
    QString query = "SELECT COUNT(*) FROM Users WHERE login = '" + login + "';";

    state = mysql_query(connection, query.toStdString().c_str());

    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
    }

    result = mysql_store_result(connection);

    row = mysql_fetch_row(result);
    QString numUsers = row[0];

    // If the count for the given login is 0 - login is unique
    if(numUsers.toInt() == 0)
        return true;
    else
        return false;
}

bool DBServer::loginAndPasswordCorrect(QString login, QString password)
{
    // See if the password matches the login
    QString query = "SELECT COUNT(*) FROM Users WHERE login = '" + login + "' AND password = '" + password + "';";

    state = mysql_query(connection, query.toStdString().c_str());

    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
    }

    result = mysql_store_result(connection);

    row = mysql_fetch_row(result);
    QString numUsers = row[0];

    // If the DB didn't return any matches to the login/password tuple - wrong password
    if(numUsers.toInt() == 0)
    {
        return false;
    }
    // Otherwise - password was correct
    else
    {
        return true;
    }
}

/**
 * @brief DBServer::checkUniqueGroup - checks if the given group name is unique
 * @param groupID - groupname to be checked
 * @return - true if it is unique, false if it already exists in the DB
 */
bool DBServer::checkUniqueGroup(QString groupID)
{
    QString query = "SELECT COUNT(*) FROM Users WHERE groupid = '" + groupID + "';";

    state = mysql_query(connection, query.toStdString().c_str());

    if (state != 0)
    {
       std::cout << mysql_error(connection) << std::endl;
    }

    result = mysql_store_result(connection);

    row = mysql_fetch_row(result);
    QString numUsers = row[0];

    // If the count for the given group name is 0 - group name is unique
    if(numUsers.toInt() == 0)
        return true;
    else
        return false;
}

/**
 * @brief DBServer::newPlayer - creates a new player in the DB
 * @param login - username that the new client wants to use
 * @param password - password to be associated with new username
 * @return - true if the username was available and the user was successfully
 * added to the DB. False otherwise.
 */
QString DBServer::newPlayer(QString login, QString password, QString groupID, QString groupPsswrd, QString admin)
{
    QString query;

    // To sign up, login must be unique
    if (checkUniqueLogin(login))
    {
        // Sign up for Admin:
        if (admin.toInt() == 1)
        {
            // Check for unique groupID - if true - register admin user
            if (checkUniqueGroup(groupID))
            {
                query = "INSERT INTO Users (login, password, highScore, votes, isAdmin, currCandidate, ";
                query += "defHill, defCruz, defKas, defBern, defTrump, groupid, groupPword) VALUES ('" + login + "', '" + password + "', 0," +
                        " 0, 1, -1, 0, 0, 0, 0, 0, '" + groupID + "', '" + groupPsswrd + "');";
                state = mysql_query(connection, query.toStdString().c_str());
                if (state != 0)
                {
                    // Need to return error saying db error
                    return "There was an error connecting to database.";
                }
            }
            // Otherwise - return error, group ID must be unique
            else
                // Need to return error saying group ID exists
                return "The group ID entered already exists";
        }
        // Sign up for non-admin
        else if (admin.toInt() == 0)
        {
            // If no group ID given - register new user with no group
            if (groupID.isEmpty())
            {
                query = "INSERT INTO Users (login, password, highScore, votes, isAdmin, currCandidate, ";
                query += "defHill, defCruz, defKas, defBern, defTrump, groupid, groupPword) VALUES ('" + login + "', '" + password + "', 0," +
                        " 0, 0, -1, 0, 0, 0, 0, 0, '', '');";
                state = mysql_query(connection, query.toStdString().c_str());
                if (state != 0)
                {
                    // Need to return error saying db error
                    return "There was an error connecting to the database";
                }
            }
            // Otherwise - check if group exists
            else
            {
                // If the group name is unique - group doesn't exist - error
                if (checkUniqueGroup(groupID))
                {
                    // Need to return error saying group doesn't exist
                    return "The group entered does not exist currently";
                }
                // Otherwise, check if the password is also correct
                else
                {
                    // Query database to get the correct group password for given group
                    query = "SELECT password FROM Users WHERE groupID = '" + groupID + "' and isAdmin = '1'";
                    state = mysql_query(connection, query.toStdString().c_str());
                    if (state != 0)
                    {
                        // Need to return error saying db error
                        return "There was an error connecting to the database";
                    }
                    result = mysql_store_result(connection);

                    row = mysql_fetch_row(result);
                    // If the group passwords match - sign up new user with the group
                    if (row[0] == groupPsswrd)
                    {
                        query = "INSERT INTO Users (login, password, highScore, votes, isAdmin, currCandidate, ";
                        query += "defHill, defCruz, defKas, defBern, defTrump, groupid, groupPword) VALUES ('" + login + "', '" + password + "', 0," +
                                " 0, 0, -1, 0, 0, 0, 0, 0, '" + groupID + "', '" + groupPsswrd + "');";
                        state = mysql_query(connection, query.toStdString().c_str());
                        if (state != 0)
                        {
                            // Need to return error saying db error
                            return "There was an error connecting to the database";
                        }
                    }
                    // Otherwise - password was wrong
                    else
                    {
                        // Need to return error saying group password wrong
                        return "The group password entered is incorrect.";
                    }
                }
            }
        }
    }
    else
        // Need to return error saying login exists
        return "The login entered exists already";

    return "";
}

/**
* @brief DBServer::checkIfUserIsAdmin
* @param username
* @return
*/
bool DBServer::checkIfUserIsAdmin(QString username)
{
   if(!checkUniqueLogin(username))
   {
        qDebug() << "login exists";
        QString query = "SELECT isAdmin FROM Users WHERE Users.login = '" + username + "';";

         state = mysql_query(connection, query.toStdString().c_str());

         if(state != 0)
         {
             std::cout << mysql_error(connection) << std::endl;
         }

         result = mysql_store_result(connection);

         row = mysql_fetch_row(result);
         QString adminStatus = row[0];

         // If the adminStatus is 1, then the username is a admin
         if(adminStatus.toInt() == 1)
             return true;
     }
     return false;
 }


/**
 * @brief DBServer::getUserInfo - helper method to retrieve all stored user info
 * when a user successfully logs in.
 * @param login - username
 * @return - a list of all their previous game info so they can continue where they left off.
 */
QList<QString> DBServer::getUserInfo(QString login)
{
    QList<QString> playerInfo;

    // Get all previous user info from DB
    QString query = "SELECT login, highScore, votes, currCandidate, defHill, defCruz, defKas, defBern, defTrump, groupid FROM Users WHERE login = '" + login + "';";
    state = mysql_query(connection, query.toStdString().c_str());

    if (state != 0)
    {
        return playerInfo;
    }
    else
    {
        result = mysql_store_result(connection);

        // Add all info to the list and return
        row = mysql_fetch_row(result);
        for(int i = 0; i < result->field_count; i++)
        {
            playerInfo.append(row[i]);
        }
        return playerInfo;
    }
}

/**
 * @brief DBServer::getLeaderboard - retrieves the leaderboard for all players or
 * leaderboard for the given group
 * @param group - either "null" for leaderboard of all players, or a valid group name
 * @return - a list of lists. inner lists hold user info and outer list is a list of users.
 */
QList<QList<QString> > DBServer::getLeaderboard(QString group)
{
    QString query;
    QList<QList<QString> > rows;

    // If no group name given - send top ten players for all groups
    if (group == "null")
    {
        query = "SELECT login, highscore FROM Users ORDER BY highscore DESC LIMIT 10;";
    }
    // Otherwise - check if group name is valid then send all players within that group
    else if(!checkUniqueGroup(group))
    {
        query = "SELECT login, highscore FROM Users WHERE groupid = '" + group + "' ORDER BY highscore DESC;";
    }
    // This means the group name didn't exist in DB
    else
        return rows;

    // No matter what - get rows from query
    state = mysql_query(connection, query.toStdString().c_str());

    if (state != 0)
    {
        return rows;
    }

    result = mysql_store_result(connection);

    // For every row in the result set - fetch row and extract info
    for (int i = 0; i < result->row_count; i++)
    {
        row = mysql_fetch_row(result);
        QList<QString> user;
        // For item in row - add info to user list
        for (int j = 0; j < 2; j++)
        {
            user.append(row[j]);
        }
        // Add user list to list of users
        rows.append(user);
    }
    return rows;
}

/**
 * @brief DBServer::dropout - drop out a player - reset current score, current character
 * and all defeated candidates.
 * @param login - username for user that dropped out
 */
void DBServer::dropout(QString login)
{
    QString query = "UPDATE Users SET votes = 0, currCandidate = -1, defHill = 0, defCruz = 0, defKas = 0, defBern = 0, defTrump = 0 WHERE login = '" + login + "';";
    state = mysql_query(connection, query.toStdString().c_str());

    if (state != 0)
    {
        // TODO - error message?
        return;
    }
}

/**
 * @brief DBServer::characterSelect - sets the current character in the DB
 * for the given user.
 * @param login - username for current user
 * @param candidate - the candidate that they chose.
 */
void DBServer::characterSelect(QString login, QString candidate)
{
    QString query;

    query = "UPDATE Users SET currCandidate = " + candidate + " WHERE login = '" + login + "';";

    state = mysql_query(connection, query.toStdString().c_str());

    if (state != 0)
    {
        // TODO error message?
        return;
    }
}

/**
 * @brief DBServer::deleteAccount
 * @return
 */
bool DBServer::deleteAccount(QString account)
{
    QString query;
    if(!checkUniqueLogin(account))
    {
        query = "DELETE FROM Users WHERE Users.login=\"" + account + "\";";
        state = mysql_query(connection, query.toStdString().c_str());

        if(state != 0)
        {
            qDebug() << "can't contact server";
            std::cout << mysql_error(connection) << std::endl;
            return false;
        }
        else
        {
            return true;
        }
    }

    return false;
}



