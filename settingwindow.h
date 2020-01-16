#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QMainWindow>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void showMenu();
    void showSystemInfo();
    void showTimeSetting();

public:
    explicit SettingWindow(QWidget *parent = nullptr);
    ~SettingWindow();

private slots:
    void on_returnButton_clicked();
    void receiveMenu();
    void receiveTimeSetting();
    void receiveSystemInfo();
    void timerUpdate();
    void on_systemInfoButton_clicked();
    void on_timeButton_clicked();

private:
    Ui::SettingWindow *ui;
    QTimer *timer;
};

#endif // SETTINGWINDOW_H
