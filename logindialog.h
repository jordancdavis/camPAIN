#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();


signals:
    void loginButtonClicked(QString,QString);
    void switchToWindow(int);
    void sendGameInfo(QStringList);

private slots:
    void on_joinButton_clicked();
    void on_cancelButton_clicked();
    void receiveLoginInfo(QStringList);

private:
    Ui::LoginDialog *ui;
    void resetWindow();
};

#endif // LOGINDIALOG_H
