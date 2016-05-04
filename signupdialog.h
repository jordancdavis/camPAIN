#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class SignUpDialog;
}

class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = 0);
    ~SignUpDialog();

signals:
    void joinButtonClicked(QString,QString,QString,QString, bool);

private slots:
    void on_cancelButton_clicked();
    void on_joinButton_clicked();
    void checkSignupErrors(QString);

private:
    Ui::SignUpDialog *ui;
    void resetWindow();
};

#endif // SIGNUPDIALOG_H
