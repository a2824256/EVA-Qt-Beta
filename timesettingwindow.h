#ifndef TIMESETTINGWINDOW_H
#define TIMESETTINGWINDOW_H

#include <QMainWindow>

namespace Ui {
class TimeSettingWindow;
}

class TimeSettingWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void showSetting();
public:
    explicit TimeSettingWindow(QWidget *parent = nullptr);
    ~TimeSettingWindow();

private:
    Ui::TimeSettingWindow *ui;
    QTimer *timer;

private slots:
    void timerUpdate();
    void receiveSetting();

    void on_returnButton_clicked();
};


#endif // TIMESETTINGWINDOW_H
