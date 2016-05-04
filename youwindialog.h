#ifndef YOUWINDIALOG_H
#define YOUWINDIALOG_H

#include <QDialog>

namespace Ui {
class YouWinDialog;
}

class YouWinDialog : public QDialog
{
    Q_OBJECT

public:
    explicit YouWinDialog(QWidget *parent = 0);
    ~YouWinDialog();

private slots:
    void on_joinButton_clicked();

private:
    Ui::YouWinDialog *ui;
};

#endif // YOUWINDIALOG_H
