#ifndef WORLDSETTINGSWINDOW_H
#define WORLDSETTINGSWINDOW_H

#include <QDialog>

namespace Ui {
class WorldSettingsWindow;
}

class WorldSettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WorldSettingsWindow(QWidget *parent = 0);
    ~WorldSettingsWindow();
    float gravity;
    float bounce;
    float oppBounce;

signals:
    void updateWorld(float, float, float);

private slots:
    void on_joinButton_clicked();
    void on_cancelButton_clicked();
    void on_gravitySlider_actionTriggered(int action);
    void on_bounceSlider_actionTriggered(int action);
    void on_frictionSlider_actionTriggered(int action);

private:
    Ui::WorldSettingsWindow *ui;
    void resetWindow();
    void updateLabels();

};

#endif // WORLDSETTINGSWINDOW_H
