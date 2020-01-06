#ifndef TIMESETTINGWINDOW_H
#define TIMESETTINGWINDOW_H

#include <QMainWindow>

namespace Ui {
class TimeSettingWindow;
}

class TimeSettingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TimeSettingWindow(QWidget *parent = nullptr);
    ~TimeSettingWindow();

private:
    Ui::TimeSettingWindow *ui;
    QTimer *timer;

private slots:
    void timerUpdate();

};


#endif // TIMESETTINGWINDOW_H
