#ifndef BIODIALOG_H
#define BIODIALOG_H

#include <QDialog>

namespace Ui {
class BioDialog;
}

class BioDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BioDialog(QWidget *parent = 0);
    ~BioDialog();
    void updateInfo(QString, QString, QString, QString, QString, QString);

private slots:
    void on_doneButton_clicked();

private:
    Ui::BioDialog *ui;
};

#endif // BIODIALOG_H
